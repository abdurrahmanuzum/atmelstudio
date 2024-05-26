/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

struct timer_descriptor TIMER_0;

void TIMER_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TCC0);
	_gclk_enable_channel(TCC0_GCLK_ID, CONF_GCLK_TCC0_SRC);
}

void TIMER_0_init(void)
{
	TIMER_0_CLOCK_init();
	timer_init(&TIMER_0, TCC0, _tcc_get_timer());
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA19

	gpio_set_pin_level(LC1_SCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(LC1_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(LC1_SCK, GPIO_PIN_FUNCTION_OFF);

	TIMER_0_init();
}
