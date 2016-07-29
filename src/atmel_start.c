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

/*! The buffer size for USART */
#define EDBG_COM_BUFFER_SIZE 16
/*! The buffer size for ADC */
#define IO1_LIGHT_SENS_BUFFER_SIZE 16

extern struct _irq_descriptor *_irq_table[PERIPH_COUNT_IRQn];
extern void Default_Handler(void);

struct usart_async_descriptor EDBG_COM;
struct timer_descriptor TIMER_0;
struct adc_async_descriptor IO1_LIGHT_SENS;

static uint8_t EDBG_COM_buffer[EDBG_COM_BUFFER_SIZE];
static struct timer_task TIMER_0_task1, TIMER_0_task2;
static uint8_t IO1_LIGHT_SENS_buffer[IO1_LIGHT_SENS_BUFFER_SIZE];

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void EDBG_COM_CLOCK_init()
{
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM3_GCLK_ID_CORE,
			CONF_GCLK_SERCOM3_CORE_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM3_GCLK_ID_SLOW,
			CONF_GCLK_SERCOM3_SLOW_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));

	hri_mclk_set_APBCMASK_SERCOM3_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void EDBG_COM_PORT_init()
{
	gpio_set_pin_function(EDBG_COM_TX, PINMUX_PA22C_SERCOM3_PAD0);

	gpio_set_pin_function(EDBG_COM_RX, PINMUX_PA23C_SERCOM3_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void EDBG_COM_init(void)
{
	EDBG_COM_CLOCK_init();
	usart_async_init(&EDBG_COM, SERCOM3, EDBG_COM_buffer, EDBG_COM_BUFFER_SIZE);
	EDBG_COM_PORT_init();
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	hri_mclk_set_APBCMASK_TC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC0_GCLK_ID, CONF_GCLK_TC0_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));

	timer_init(&TIMER_0, TC0, _tc_get_timer());
}

/**
 * \brief ADC initialization function
 *
 * Enables ADC peripheral, clocks and initializes ADC driver
 */
static void IO1_LIGHT_SENS_init(void)
{
	hri_mclk_set_APBDMASK_ADC_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC_GCLK_ID, CONF_GCLK_ADC_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));
	adc_async_init(&IO1_LIGHT_SENS,
			ADC,
			IO1_LIGHT_SENS_buffer,
			IO1_LIGHT_SENS_BUFFER_SIZE);

	// Disable digital pin circuitry
	gpio_set_pin_direction(IO1_LIGHTSENSOR, GPIO_DIRECTION_OFF);
	gpio_set_pin_function(IO1_LIGHTSENSOR, PINMUX_PB05B_ADC_AIN13);
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
void TC0_Handler(void)
{
	if (_irq_table[ TC0_IRQn + 0 ]) {
		_irq_table[ TC0_IRQn + 0 ]->handler(
				_irq_table[ TC0_IRQn + 0 ]->parameter);
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
void DMAC_Handler(void)
{
	if (_irq_table[ DMAC_IRQn + 0 ]) {
		_irq_table[ DMAC_IRQn + 0 ]->handler(
				_irq_table[ DMAC_IRQn + 0 ]->parameter);
	} else {
		Default_Handler();
	}
}

/**
 * Example of using EDBG_COM to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_EDBG_COM[12] = "Hello World!";

static void tx_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void EDBG_COM_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&EDBG_COM, USART_ASYNC_TXC_CB, tx_cb_EDBG_COM);
	/*usart_async_register_callback(&EDBG_COM, USART_ASYNC_RXC_CB, rx_cb);
	   usart_async_register_callback(&EDBG_COM, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&EDBG_COM, &io);
	usart_async_enable(&EDBG_COM);

	io_write(io, example_EDBG_COM, 12);
}

/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb = TIMER_0_task1_cb;
	TIMER_0_task1.mode = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb = TIMER_0_task2_cb;
	TIMER_0_task2.mode = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

static void convert_cb_IO1_LIGHT_SENS(
		const struct adc_async_descriptor *const descr)
{
}

/**
 * Example of using IO1_LIGHT_SENS to generate waveform.
 */
void IO1_LIGHT_SENS_example(void)
{
	adc_async_register_callback(&IO1_LIGHT_SENS,
			ADC_ASYNC_CONVERT_CB,
			convert_cb_IO1_LIGHT_SENS);
	adc_async_enable(&IO1_LIGHT_SENS);
	adc_async_start_conversion(&IO1_LIGHT_SENS);
}

void system_init(void)
{
	init_mcu();

	EDBG_COM_init();
	TIMER_0_init();
	IO1_LIGHT_SENS_init();
}
