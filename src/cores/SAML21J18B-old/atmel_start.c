/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "atmel_start.h"
#include <utils.h>
#include <hal_init.h>
#include <hpl_irq.h>
#include <hri_gclk2_v111.h>
#include <hri_mclk_v101.h>
#include <peripheral_gclk_config.h>

extern struct _irq_descriptor *_irq_table[PERIPH_COUNT_IRQn];
extern void Default_Handler(void);

struct adc_sync_descriptor ADC_0;

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
void ADC_0_PORT_init(void)
{
	// Disable digital pin circuitry
	gpio_set_pin_direction(PA03, GPIO_DIRECTION_OFF);
	gpio_set_pin_function(PA03, PINMUX_PA03B_ADC_AIN1);
}

void ADC_0_CLOCK_init(void)
{
	hri_mclk_set_APBDMASK_ADC_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC_GCLK_ID, CONF_GCLK_ADC_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));
}
void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC);
}

/**
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable(&ADC_0);

	while (1) 
	{
		adc_sync_read(&ADC_0, buffer, 2);
	}
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

void delay_example(void)
{
	delay_ms(5000);
}

void SERCOM3_Handler(void)
{
	if (_irq_table[ SERCOM0_IRQn + 3 ]) {
		_irq_table[ SERCOM0_IRQn + 3 ]->handler(
				_irq_table[ SERCOM0_IRQn + 3 ]->parameter);
	} else {
		Default_Handler();
	}
}

void ADC_Handler(void)
{
	if (_irq_table[ ADC_IRQn + 0 ]) {
		_irq_table[ ADC_IRQn + 0 ]->handler(
				_irq_table[ ADC_IRQn + 0 ]->parameter);
	} else {
		Default_Handler();
	}
}

void RTC_Handler(void)
{
	if (_irq_table[ RTC_IRQn + 0 ]) {
		_irq_table[ RTC_IRQn + 0 ]->handler(
				_irq_table[ RTC_IRQn + 0 ]->parameter);
	} else {
		Default_Handler();
	}
}

void MCLK_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void OSCCTRL_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}
void OSC32KCTRL_Handler(void)
{
	if (_irq_table[  +0 ]) {
		_irq_table[  +0 ]->handler(_irq_table[  +0 ]->parameter);
	} else {
		Default_Handler();
	}
}


void system_init(void)
{
	init_mcu();

	// Set pin direction to output
	gpio_set_pin_direction(LED0, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(LED0,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(LED0, GPIO_PIN_FUNCTION_OFF);

	ADC_0_init();
	delay_driver_init();
}
