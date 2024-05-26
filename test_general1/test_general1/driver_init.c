/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

#include <hpl_adc_base.h>
#include <hpl_rtc_base.h>

struct timer_descriptor TIMER_0;

struct adc_sync_descriptor ADC_0;

struct usart_sync_descriptor USART_0;

struct dac_sync_descriptor DAC_0;

void ADC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(AIN_1, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(AIN_1, PINMUX_PA04B_ADC_AIN4);

	// Disable digital pin circuitry
	gpio_set_pin_direction(AIN_2, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(AIN_2, PINMUX_PA05B_ADC_AIN5);
}

void ADC_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, ADC);
	_gclk_enable_channel(ADC_GCLK_ID, CONF_GCLK_ADC_SRC);
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC, (void *)NULL);
}

void EXTERNAL_IRQ_0_init(void)
{
	_gclk_enable_channel(EIC_GCLK_ID, CONF_GCLK_EIC_SRC);

	// Set pin direction to input
	gpio_set_pin_direction(PA16, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA16,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA16, PINMUX_PA16A_EIC_EXTINT0);

	// Set pin direction to input
	gpio_set_pin_direction(PA17, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA17,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA17, PINMUX_PA17A_EIC_EXTINT1);

	ext_irq_init();
}

void USART_0_PORT_init(void)
{

	gpio_set_pin_function(U0_TX, PINMUX_PA00D_SERCOM1_PAD0);

	gpio_set_pin_function(U0_RX, PINMUX_PA01D_SERCOM1_PAD1);
}

void USART_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM1);
	_gclk_enable_channel(SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC);
}

void USART_0_init(void)
{
	USART_0_CLOCK_init();
	usart_sync_init(&USART_0, SERCOM1, (void *)NULL);
	USART_0_PORT_init();
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBA, RTC);
	_gclk_enable_channel(RTC_GCLK_ID, CONF_GCLK_RTC_SRC);
	timer_init(&TIMER_0, RTC, _rtc_get_timer());
}

void DAC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(DAC_O, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(DAC_O, PINMUX_PA02B_DAC_VOUT);

	// Disable digital pin circuitry
	gpio_set_pin_direction(DAC_VREF, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(DAC_VREF, PINMUX_PA03B_DAC_VREFP);
}

void DAC_0_CLOCK_init(void)
{

	_pm_enable_bus_clock(PM_BUS_APBC, DAC);
	_gclk_enable_channel(DAC_GCLK_ID, CONF_GCLK_DAC_SRC);
}

void DAC_0_init(void)
{
	DAC_0_CLOCK_init();
	dac_sync_init(&DAC_0, DAC);
	DAC_0_PORT_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA08

	// Set pin direction to input
	gpio_set_pin_direction(DIN_NP, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DIN_NP,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DIN_NP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA09

	// Set pin direction to input
	gpio_set_pin_direction(DIN_PD, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DIN_PD,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_DOWN);

	gpio_set_pin_function(DIN_PD, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA10

	gpio_set_pin_level(DIO_1,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(DIO_1, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(DIO_1, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA11

	gpio_set_pin_level(DIO_2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(DIO_2, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(DIO_2, GPIO_PIN_FUNCTION_OFF);

	ADC_0_init();
	EXTERNAL_IRQ_0_init();

	USART_0_init();

	delay_driver_init();

	TIMER_0_init();

	DAC_0_init();
}
