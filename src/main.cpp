
extern "C"
{
	#include "atmel_start.h"
}

static volatile uint8_t powermode = 0;
static volatile uint8_t welcome = 0;
static volatile uint8_t echoback = 0;

/* Local declare for USART */
static uint8_t rx_char;
const static uint8_t str_welcome[42] = "Lower Power Demo 1.  Blinking LED... \r\n";
const static uint8_t str_goto_lowpower[65] = "Entering Low Power Mode: echo chars until \"s\" is pressed: \r\n";

/**
 * \brief Put the system to sleep waiting for interrupt.
 *
 * Executes a device DSB (Data Synchronization Barrier) instruction to ensure
 * all ongoing memory accesses have completed, then a WFI (Wait For Interrupt)
 * instruction to place the device into the sleep mode until woken by an interrupt.
 */
static void demo_system_sleep(void)
{
	/** Avoid PB10(LED) power consumption */
	PORT->Group[1].PINCFG[10].bit.PULLEN = 1;
	__DSB();
	__WFI();
	PORT->Group[1].PINCFG[10].bit.PULLEN = 0;
}

/**
 * \brief Set the sleep mode of the device.
 *
 * Sets the sleep mode of the device; the configured sleep mode will be entered
 * upon the next call of the \ref demo_system_sleep() function.
 */
static void demo_set_sleepmode_STANDBY()
{
	/* 1. Set buck regulator as Main Voltage Regulator */
	SUPC->VREG.bit.SEL = 1;
	while(SUPC->STATUS.bit.VCORERDY != 1);

	/* 2. Enable dynamic power domain gating for PD0/1 */
	PM->STDBYCFG.bit.DPGPD0 = 1;
	PM->STDBYCFG.bit.DPGPD1 = 1;

	/* 3. Enable VREG to run on demand */
	SUPC->VREG.bit.RUNSTDBY = 1;
	#ifndef SAM_L21_REV_A
	//SUPC->VREG.bit.LPEFF    = 1;
	#endif

	/* 4. Set STANDBY as sleep mode */
	PM->SLEEPCFG.reg = PM_SLEEPCFG_SLEEPMODE_STANDBY;
	while (PM->SLEEPCFG.reg != PM_SLEEPCFG_SLEEPMODE_STANDBY);
}

static void demo_run(void)
{
	uint32_t blink_led = 3;

	/* Print hello info */
	io_write(&EDBG_COM.io, str_welcome, 39);

	/* Blink LED 3 times */
	while (blink_led--)	{
		gpio_set_pin_level(LED0, false);
		delay_ms(500);
		gpio_set_pin_level(LED0, true);
		delay_ms(500);
	}

	/* Output sleep info */
	io_write(&EDBG_COM.io, str_goto_lowpower, 60);
}


/**
 * Timer
 */
static struct timer_task demo_timer_task1;

static void demo_timer_sleep_cb(const struct timer_task *const timer_task)
{
	powermode = 1;
}

/**
 * COM Port receive callback
 */
static void demo_rx_cb_COM(const struct usart_async_descriptor *const io_descr)
{
	powermode = 0;
	int32_t rx_len;

	/* Read input character */
	rx_len = io_read(&EDBG_COM.io, &rx_char, 1);
	if (rx_len != 1) {
		return;
	}

	SUPC->VREF.reg &= ~(1 << 8);

	/* Discard input during welcome */
	if (welcome == 1) {
		return;
	}

	/* Goto Low Power Mode */
	if (rx_char == 's') {
		welcome = 1;
		return;
	}

	/* Echo back input character */
	echoback = 1;
	timer_add_task(&TIMER_0, &demo_timer_task1);
}

static void demo_init(void)
{
	/** Set STANDBY as sleep mode */
	demo_set_sleepmode_STANDBY();

	/** Init COM Port */
	usart_async_register_callback(&EDBG_COM, USART_ASYNC_RXC_CB, demo_rx_cb_COM);
	usart_async_enable(&EDBG_COM);

	/* Avoid PORT power consumption */
	gpio_set_pin_pull_mode(SW0,	GPIO_PULL_UP);
	gpio_set_pin_pull_mode(EDBG_COM_RX,	GPIO_PULL_UP);
	gpio_set_pin_pull_mode(EDBG_SPI_MOSI, GPIO_PULL_UP);
	gpio_set_pin_pull_mode(EDBG_SPI_MISO, GPIO_PULL_UP);
	gpio_set_pin_pull_mode(EDBG_SPI_SCK, GPIO_PULL_UP);

	demo_timer_task1.interval = 1000;
	demo_timer_task1.cb = demo_timer_sleep_cb;
	demo_timer_task1.mode = TIMER_TASK_ONE_SHOT;

	timer_start(&TIMER_0);
}

int main(void)
{
	system_init();
	demo_init();
	powermode = 1;
	welcome = 1;

	while(1) {
		if (welcome) {
			demo_run();
			welcome = 0;
			powermode = 1;
		}
		if (echoback) {
			echoback = 0;
			io_write(&EDBG_COM.io, &rx_char, 1);
		}
		if (powermode) {
			demo_system_sleep();
		}
	};
}
