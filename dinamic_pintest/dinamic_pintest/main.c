#include <atmel_start.h>

void isr1 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK1, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK1, 0 );
	}
}

void isr2 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK2, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK2, 0 );
	}
}

void isr3 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK3, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK3, 0 );
	}
}

void isr4 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK4, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK4, 0 );
	}
}

void isr5 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK5, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK5, 0 );
	}
}

void isr6 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK6, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK6, 0 );
	}
}

void isr7 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK7, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK7, 0 );
	}
}

void isr8 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK8, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK8, 0 );
	}
}

void isr9 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK9, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK9, 0 );
	}
}

void isr10 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK10, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK10, 0 );
	}
}

void isr11 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK11, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK11, 0 );
	}
}

void isr12 ( void )
{
	for ( int i = 0; i < 25; i++ )
	{
		gpio_set_pin_level( SCK12, 1 );
		delay_us(1);
		gpio_set_pin_level( SCK12, 0 );
	}
}







int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	ext_irq_register( DOUT1, isr1 );
	ext_irq_register( DOUT2, isr2 );
	ext_irq_register( DOUT3, isr3 );
	ext_irq_register( DOUT4, isr4 );
	ext_irq_register( DOUT5, isr5 );
	ext_irq_register( DOUT6, isr6 );
	ext_irq_register( DOUT7, isr7 );
	ext_irq_register( DOUT8, isr8 );
	ext_irq_register( DOUT9, isr9 );
	ext_irq_register( DOUT10, isr10 );
	ext_irq_register( DOUT11, isr11 );
	ext_irq_register( DOUT12, isr12 );
	
	
	
	/* Replace with your application code */
	for ( ;; )
	{
		//gpio_toggle_pin_level( SCK1 );
		//gpio_toggle_pin_level( SCK2 );
		//gpio_toggle_pin_level( SCK3 );
		//gpio_toggle_pin_level( SCK4 );
		//gpio_toggle_pin_level( SCK5 );
		//gpio_toggle_pin_level( SCK6 );
		//gpio_toggle_pin_level( SCK7 );
		//gpio_toggle_pin_level( SCK8 );
		//gpio_toggle_pin_level( SCK9 );
		//gpio_toggle_pin_level( SCK10 );
		//gpio_toggle_pin_level( SCK11 );
		//gpio_toggle_pin_level( SCK12 );
		//
		//delay_ms( 10 );
	}
}
