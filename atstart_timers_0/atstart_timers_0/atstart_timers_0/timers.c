#include "timers.h"


static void cb_poke_adc( const struct timer_task *const timer_task )
{
	gpio_toggle_pin_level( LC1_SCK );
}

void setup_timer( void )
{
	struct timer_task timer_task_config;
	
	timer_task_config.interval	= 1000;				// us
	timer_task_config.cb		= cb_poke_adc;		// callback function pointer
	timer_task_config.mode		= TIMER_TASK_REPEAT;
	
	timer_add_task( &TIMER_0, &timer_task_config );
}
