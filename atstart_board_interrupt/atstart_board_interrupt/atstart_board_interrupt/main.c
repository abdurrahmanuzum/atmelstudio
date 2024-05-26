#include <atmel_start.h>


void irqcallback( void )
{
	gpio_toggle_pin_level( LED );
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	ext_irq_register( 15, irqcallback );

	/* Replace with your application code */
	while (1) 
	{

	}
}
