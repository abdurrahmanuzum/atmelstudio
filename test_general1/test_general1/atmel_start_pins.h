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

#define U0_TX GPIO(GPIO_PORTA, 0)
#define U0_RX GPIO(GPIO_PORTA, 1)
#define DAC_O GPIO(GPIO_PORTA, 2)
#define DAC_VREF GPIO(GPIO_PORTA, 3)
#define AIN_1 GPIO(GPIO_PORTA, 4)
#define AIN_2 GPIO(GPIO_PORTA, 5)
#define DIN_NP GPIO(GPIO_PORTA, 8)
#define DIN_PD GPIO(GPIO_PORTA, 9)
#define DIO_1 GPIO(GPIO_PORTA, 10)
#define DIO_2 GPIO(GPIO_PORTA, 11)
#define PA16 GPIO(GPIO_PORTA, 16)
#define PA17 GPIO(GPIO_PORTA, 17)

#endif // ATMEL_START_PINS_H_INCLUDED
