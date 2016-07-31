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

extern struct _irq_descriptor *_irq_table[PERIPH_COUNT_IRQn];
extern void Default_Handler(void);

struct usart_async_descriptor EDBG_COM;
struct spi_m_sync_descriptor EDBG_SPI;
struct timer_descriptor TIMER_0;

static uint8_t EDBG_COM_buffer[EDBG_COM_BUFFER_SIZE];
static struct timer_task TIMER_0_task1, TIMER_0_task2;

struct adc_sync_descriptor ADC_0;

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

void EDBG_SPI_PORT_init(void)
{
	// Set pin direction to input
	gpio_set_pin_direction(EDBG_SPI_MISO, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(EDBG_SPI_MISO,
	        // <y> Pull configuration
	        // <id> pad_pull_config
	        // <GPIO_PULL_OFF"> Off
	        // <GPIO_PULL_UP"> Pull-up
	        // <GPIO_PULL_DOWN"> Pull-down
			GPIO_PULL_OFF);

	gpio_set_pin_function(EDBG_SPI_MISO, PINMUX_PB16C_SERCOM5_PAD0);

	// Set pin direction to output
	gpio_set_pin_direction(EDBG_SPI_MOSI, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EDBG_SPI_MOSI,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(EDBG_SPI_MOSI, PINMUX_PB22D_SERCOM5_PAD2);

	// Set pin direction to output
	gpio_set_pin_direction(EDBG_SPI_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(EDBG_SPI_SCK,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(EDBG_SPI_SCK, PINMUX_PB23D_SERCOM5_PAD3);
}
void EDBG_SPI_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM5_GCLK_ID_CORE,
			CONF_GCLK_SERCOM5_CORE_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));
	hri_gclk_write_PCHCTRL_reg(GCLK,
			SERCOM5_GCLK_ID_SLOW,
			CONF_GCLK_SERCOM5_SLOW_SRC |
			( 1 << GCLK_PCHCTRL_CHEN_Pos ));

	hri_mclk_set_APBDMASK_SERCOM5_bit(MCLK);
}
void EDBG_SPI_init(void)
{
	EDBG_SPI_CLOCK_init();
	spi_m_sync_init(&EDBG_SPI, SERCOM5);
	EDBG_SPI_PORT_init();
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

	while (1) {
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
void SERCOM5_Handler(void)
{
	if (_irq_table[ SERCOM0_IRQn + 5 ]) {
		_irq_table[ SERCOM0_IRQn + 5 ]->handler(
				_irq_table[ SERCOM0_IRQn + 5 ]->parameter);
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
 * Example of using EDBG_SPI to write "Hello World" using the IO abstraction.
 */
static uint8_t example_EDBG_SPI[12] = "Hello World!";

void EDBG_SPI_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&EDBG_SPI, &io);

	spi_m_sync_enable(&EDBG_SPI);
	io_write(io, example_EDBG_SPI, 12);
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

void system_init(void)
{
	init_mcu();

	// GPIO on PA02

	// Set pin direction to input
	gpio_set_pin_direction(SW0, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(SW0,
	        // <y> Pull configuration
	        // <id> pad_pull_config
	        // <GPIO_PULL_OFF"> Off
	        // <GPIO_PULL_UP"> Pull-up
	        // <GPIO_PULL_DOWN"> Pull-down
			GPIO_PULL_UP);

	gpio_set_pin_function(SW0, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB10

	// Set pin direction to output
	gpio_set_pin_direction(LED0, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(LED0,
	        // <y> Initial level
	        // <id> pad_initial_level
	        // <false"> Low
	        // <true"> High
			false);

	gpio_set_pin_function(LED0, GPIO_PIN_FUNCTION_OFF);

	EDBG_COM_init();

	EDBG_SPI_init();
	TIMER_0_init();

	ADC_0_init();

	delay_driver_init();
}
