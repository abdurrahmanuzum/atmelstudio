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

#define pwm3 GPIO(GPIO_PORTA, 15)
#define pwm1 GPIO(GPIO_PORTA, 18)
#define pwm2 GPIO(GPIO_PORTA, 19)
#define pin1 GPIO(GPIO_PORTB, 6)
#define pin2 GPIO(GPIO_PORTB, 7)
#define LED GPIO(GPIO_PORTB, 30)

#endif // ATMEL_START_PINS_H_INCLUDED
