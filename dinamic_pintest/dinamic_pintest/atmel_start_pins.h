/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define SCK12 GPIO(GPIO_PORTA, 8)
#define DOUT12 GPIO(GPIO_PORTA, 9)
#define SCK11 GPIO(GPIO_PORTA, 10)
#define DOUT11 GPIO(GPIO_PORTA, 11)
#define DOUT7 GPIO(GPIO_PORTA, 12)
#define SCK7 GPIO(GPIO_PORTA, 13)
#define SCK1 GPIO(GPIO_PORTA, 22)
#define DOUT1 GPIO(GPIO_PORTA, 23)
#define SCK3 GPIO(GPIO_PORTA, 27)
#define DOUT3 GPIO(GPIO_PORTA, 28)
#define DOUT5 GPIO(GPIO_PORTB, 0)
#define SCK5 GPIO(GPIO_PORTB, 1)
#define DOUT6 GPIO(GPIO_PORTB, 2)
#define SCK6 GPIO(GPIO_PORTB, 3)
#define DOUT10 GPIO(GPIO_PORTB, 10)
#define SCK10 GPIO(GPIO_PORTB, 11)
#define SCK9 GPIO(GPIO_PORTB, 12)
#define DOUT9 GPIO(GPIO_PORTB, 13)
#define SCK8 GPIO(GPIO_PORTB, 14)
#define DOUT8 GPIO(GPIO_PORTB, 15)
#define DOUT2 GPIO(GPIO_PORTB, 22)
#define SCK2 GPIO(GPIO_PORTB, 23)
#define DOUT4 GPIO(GPIO_PORTB, 30)
#define SCK4 GPIO(GPIO_PORTB, 31)

#endif // ATMEL_START_PINS_H_INCLUDED
