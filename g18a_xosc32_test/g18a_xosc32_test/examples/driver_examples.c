/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

static void button_on_PB03_pressed(void)
{
}

static void button_on_PA06_pressed(void)
{
}

static void button_on_PB09_pressed(void)
{
}

static void button_on_PA10_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{

	ext_irq_register(PIN_PB03, button_on_PB03_pressed);
	ext_irq_register(PIN_PA06, button_on_PA06_pressed);
	ext_irq_register(PIN_PB09, button_on_PB09_pressed);
	ext_irq_register(PIN_PA10, button_on_PA10_pressed);
}
