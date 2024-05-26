#include <atmel_start.h>




void irq_handler( void )
{
	gpio_toggle_pin_level( LED_HERE );
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	ext_irq_register( PIN_PA18, irq_handler );

	/* Replace with your application code */
	while (1) 
	{
		
	}
}
