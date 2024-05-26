#include <atmel_start.h>




struct timer_task task;

static void cbf ( const struct timer_task *const timer_task )
{
	gpio_toggle_pin_level( LC1_SCK );
}



int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	gpio_toggle_pin_level( LC1_SCK );
	delay_us(1000);
	gpio_toggle_pin_level( LC1_SCK );
	
	task.interval	= 1;
	task.cb			= cbf;
	task.mode		= TIMER_TASK_REPEAT;
	
	timer_add_task( &TIMER_0, &task );
	
	timer_start( &TIMER_0 );
	
	for ( ;; )
	{
		
	}
	
	
}
