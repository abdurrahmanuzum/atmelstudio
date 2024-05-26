#include <atmel_start.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	//
	usb_serial_init();

	for ( ;; )
	{
		usb_serial_puts( "TEST\r\n" );
		gpio_toggle_pin_level( PIN_LED );
		delay_ms( 500 );
	}
}
