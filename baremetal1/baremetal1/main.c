/*
 * baremetal1.c
 *
 * Created: 22/12/2022 22:21:20
 * Author : Abdurrahman
 */ 


#include "sam.h"
#include "startup.h"
#include "delay.h"


int main(void)
{
	
	clocks_init();
	pins_init();
	
    /* Replace with your application code */
    while (1) 
    {
		
		// Turn the LED on PA17 ON
		REG_PORT_OUTSET0 = LED0_PIN_MASK;
		
		// delay for one second
		delay_s(1);
		
		// turn the LED on PA17 OFF
		REG_PORT_OUTCLR0 = LED0_PIN_MASK;
		
		// delay for one second
		delay_s(1);
		
    }
}
