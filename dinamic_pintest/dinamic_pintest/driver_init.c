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

void EXTERNAL_IRQ_0_init(void)
{
	_gclk_enable_channel(EIC_GCLK_ID, CONF_GCLK_EIC_SRC);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT5, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT5,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT5, PINMUX_PB00A_EIC_EXTINT0);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT6, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT6,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT6, PINMUX_PB02A_EIC_EXTINT2);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT2, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT2,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT2, PINMUX_PB22A_EIC_EXTINT6);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT1, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT1,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT1, PINMUX_PA23A_EIC_EXTINT7);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT3, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT3,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT3, PINMUX_PA28A_EIC_EXTINT8);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT12, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT12,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT12, PINMUX_PA09A_EIC_EXTINT9);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT10, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT10,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT10, PINMUX_PB10A_EIC_EXTINT10);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT11, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT11,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT11, PINMUX_PA11A_EIC_EXTINT11);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT7, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT7,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT7, PINMUX_PA12A_EIC_EXTINT12);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT9, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT9,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT9, PINMUX_PB13A_EIC_EXTINT13);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT4, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT4,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT4, PINMUX_PB30A_EIC_EXTINT14);

	// Set pin direction to input
	gpio_set_pin_direction(DOUT8, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(DOUT8,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(DOUT8, PINMUX_PB15A_EIC_EXTINT15);

	ext_irq_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA08

	gpio_set_pin_level(SCK12,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK12, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK12, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA10

	gpio_set_pin_level(SCK11,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK11, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK11, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA13

	gpio_set_pin_level(SCK7,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK7, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK7, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA22

	gpio_set_pin_level(SCK1,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK1, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK1, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA27

	gpio_set_pin_level(SCK3,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK3, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK3, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB01

	gpio_set_pin_level(SCK5,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK5, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK5, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB03

	gpio_set_pin_level(SCK6,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK6, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK6, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB11

	gpio_set_pin_level(SCK10,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK10, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK10, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB12

	gpio_set_pin_level(SCK9,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK9, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK9, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB14

	gpio_set_pin_level(SCK8,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK8, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK8, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB23

	gpio_set_pin_level(SCK2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK2, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK2, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB31

	gpio_set_pin_level(SCK4,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(SCK4, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(SCK4, GPIO_PIN_FUNCTION_OFF);

	EXTERNAL_IRQ_0_init();
}
