/**
 * \file
 *
 * \brief Test suite core functionality
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <compiler.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include "suite.h"

/**
 * \weakgroup test_suite_group
 * @{
 */

/**
 * \internal
 * \brief Data pointer for test cases
 *
 * \see test_set_data(), test_get_data()
 */
void *test_priv_data;

/**
 * \internal
 * \brief Context saved before executing a test or fixture function.
 *
 * This is used for doing non-local jumps from the test cases on failure.
 */
static jmp_buf test_failure_jmpbuf;

/**
 * \internal
 * \brief Pointer to current test case
 *
 * \see test_set_case(), test_get_case()
 */
struct test_case *test_case_ptr = NULL;

/**
 * \internal
 * \brief Report a failing test stage
 *
 * \param test Current test case.
 * \param stage Name of test stage that failed.
 * \param result Result value of test stage.
 */
static void test_report_failure(const struct test_case *test, const char *stage,
		int result)
{
	dbg_error("Test '%s' failed during '%s': %d\r\n", test->name, stage,
			result);
}

/**
 * \internal
 * \brief Call a test or fixture function
 *
 * This function will initialize \ref test_failure_jmpbuf and call \a func
 * with \a test as the parameter.
 *
 * \param func Pointer to function to call.
 * \param test_case Pointer to the function's originating test case.
 *
 * \return #TEST_PASS if \a func was executed successfully, or the
 * result value passed to test_fail() on failure.
 */
static int test_call(void (*func)(const struct test_case *),
		const struct test_case *test)
{
	int ret = 0;

	if (!func) {
		return TEST_PASS;
	}

	/*
	 * The first call to setjmp() always return 0. However, if the
	 * call to func() below goes wrong, we'll return here again with
	 * a nonzero value.
	 */
	ret = setjmp(test_failure_jmpbuf);
	if (ret) {
		return ret;
	}

	func(test);

	return TEST_PASS;
}

/**
 * \internal
 * \brief Run a test case
 *
 * This function will call the \e setup, \e run and \e cleanup functions of the
 * specified test case, outputting debug information as it goes, then returning
 * the result value of the test case.
 *
 * If the setup stage does not pass, the rest of the test case if skipped.
 * If the test stage itself does not pass, the cleanup is still executed.
 *
 * The result from the first non-passing function in the test case is returned,
 * meaning a failing cleanup will override a successful test.
 *
 * \param test_case Test case to run.
 *
 * \return \ref TEST_PASS if all functions execute successfully. Otherwise, the
 * first non-zero value which is returned from the test case.
 */
static int test_case_run(const struct test_case *test)
{
	int result;

// Store test pointer for access by test_get_data()
#if defined(_ASSERT_ENABLE_) && defined(TEST_SUITE_DEFINE_ASSERT_MACRO)
	test_set_case(test);
#endif

	dbg_info("Running test: %s\r\n", test->name);
	if (test->setup) {
		int ret;
		dbg("Setting up fixture\r\n");
		ret = test_call(test->setup, test);
		if (ret) {
			test_report_failure(test, "setup", ret);
			return ret;
		}
	}

	result = test_call(test->run, test);
	if (result) {
		test_report_failure(test, "test", result);
	}

	if (test->cleanup) {
		int ret;
		dbg("Cleaning up fixture\r\n");
		ret = test_call(test->cleanup, test);
		if (ret && !result) {
			test_report_failure(test, "cleanup", ret);
			result = ret;
		}
	}

// Test is done, clear the stored test pointer
#if defined(_ASSERT_ENABLE_) && defined(TEST_SUITE_DEFINE_ASSERT_MACRO)
	test_set_case(NULL);
#endif

	return result;
}

/**
 * \internal
 * \brief Report a failure and jump out of current test case function
 *
 * \param test Current test case.
 * \param result Result value of failure. \note Should not be \ref TEST_PASS.
 * \param file Name of file in which function resides.
 * \param line Line number at which failure occurred.
 * \param fmt Failure message, as printf-formatted string.
 * \param ... Values to insert into failure message.
 */
void test_case_fail(const struct test_case *test, int result,
		const char *file, unsigned int line,
		const char *fmt, ...)
{
	va_list ap;

	dbg_error("Test '%s' failed at %s:%u:\r\n\t", test->name, file, line);

	va_start(ap, fmt);
	dbg_vprintf_pgm(fmt, ap);
	va_end(ap);
	dbg_putchar('\r');
	dbg_putchar('\n');

	/*
	 * This will cause the setjmp() call in test_call() to return
	 * TEST_FAIL.
	 */
	longjmp(test_failure_jmpbuf, result);
}

/**
 * \brief Run a test suite
 *
 * Run all tests in \a suite, in the order in which they are found in
 * the array.
 *
 * \return The number of tests that didn't pass.
 */
int test_suite_run(const struct test_suite *suite)
{
	unsigned int nr_failures = 0;
	unsigned int nr_errors = 0;
	unsigned int i;
	int          ret;

	dbg_info("Running test suite '%s'...\r\n", suite->name);

	for (i = 0; i < suite->nr_tests; i++) {
		const struct test_case *test;

		test = suite->tests[i];
		ret = test_case_run(test);
		if (ret < TEST_PASS) {
			nr_errors++;
		} else if (ret > TEST_PASS) {
			nr_failures++;
		}
	}

	dbg_info("Test suite '%s' complete: %u tests, %u failures, %u errors\r\n\r\n",
			suite->name, suite->nr_tests, nr_failures, nr_errors);

	return nr_errors + nr_failures;
}

//! @}
