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

static void button_on_PB00_pressed(void)
{
}

static void button_on_PB02_pressed(void)
{
}

static void button_on_PB22_pressed(void)
{
}

static void button_on_PA23_pressed(void)
{
}

static void button_on_PA28_pressed(void)
{
}

static void button_on_PA09_pressed(void)
{
}

static void button_on_PB10_pressed(void)
{
}

static void button_on_PA11_pressed(void)
{
}

static void button_on_PA12_pressed(void)
{
}

static void button_on_PB13_pressed(void)
{
}

static void button_on_PB30_pressed(void)
{
}

static void button_on_PB15_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{

	ext_irq_register(PIN_PB00, button_on_PB00_pressed);
	ext_irq_register(PIN_PB02, button_on_PB02_pressed);
	ext_irq_register(PIN_PB22, button_on_PB22_pressed);
	ext_irq_register(PIN_PA23, button_on_PA23_pressed);
	ext_irq_register(PIN_PA28, button_on_PA28_pressed);
	ext_irq_register(PIN_PA09, button_on_PA09_pressed);
	ext_irq_register(PIN_PB10, button_on_PB10_pressed);
	ext_irq_register(PIN_PA11, button_on_PA11_pressed);
	ext_irq_register(PIN_PA12, button_on_PA12_pressed);
	ext_irq_register(PIN_PB13, button_on_PB13_pressed);
	ext_irq_register(PIN_PB30, button_on_PB30_pressed);
	ext_irq_register(PIN_PB15, button_on_PB15_pressed);
}
