#include <atmel_start.h>

#include "timers.h"



int main( void )
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	delay_ms( 2000 );
	
	setup_timer();
	
	timer_start( &TIMER_0 );
	
	
	for ( ;; )
	{
		
	}
	
	
	
	
	
	
	
	
	
	
	
}
