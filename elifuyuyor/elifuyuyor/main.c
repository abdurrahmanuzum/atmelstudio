#include <atmel_start.h>

static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level( pwm1, 1 );
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level( pwm1, 0 );
}

static void TIMER_0_task3_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level( pwm2, 1 );
}

static void TIMER_0_task4_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level( pwm2, 0 );
}

static void TIMER_0_task5_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level( pwm3, 1 );
}

static void TIMER_0_task6_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level( pwm3, 0 );
}






int main( void )
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();	
	
	double duty1 = 0.5;
	double duty2 = 0.5;
	double duty3  = 0.5;

	int period = 100;

	double x1 = 1 - duty1;
	double x2 = 1 - duty2;
	double x3 = 1 - duty3;

	
	struct timer_task TIMER_0_task1, TIMER_0_task2, TIMER_0_task3, TIMER_0_task4, TIMER_0_task5, TIMER_0_task6;

	TIMER_0_task1.interval = period * x1;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	
	TIMER_0_task2.interval = period * ( 1 - x1 );
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;
	
	
	TIMER_0_task3.interval = period * x2;
	TIMER_0_task3.cb       = TIMER_0_task3_cb;
	TIMER_0_task3.mode     = TIMER_TASK_REPEAT;
	
	TIMER_0_task4.interval = period * ( 1 - x2 );
	TIMER_0_task4.cb       = TIMER_0_task4_cb;
	TIMER_0_task4.mode     = TIMER_TASK_REPEAT;
	
	
	TIMER_0_task5.interval = period * x3;
	TIMER_0_task5.cb       = TIMER_0_task5_cb;
	TIMER_0_task5.mode     = TIMER_TASK_REPEAT;
	
	TIMER_0_task6.interval = period * ( 1 - x3 );
	TIMER_0_task6.cb       = TIMER_0_task6_cb;
	TIMER_0_task6.mode     = TIMER_TASK_REPEAT;
	
	

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_add_task(&TIMER_0, &TIMER_0_task3);
	timer_add_task(&TIMER_0, &TIMER_0_task4);
	timer_add_task(&TIMER_0, &TIMER_0_task5);
	timer_add_task(&TIMER_0, &TIMER_0_task6);
	
	timer_start(&TIMER_0);
	
	/* Replace with your application code */
	for ( ;; )
	{
				
	}
	
}
