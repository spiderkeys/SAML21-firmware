extern "C"
{
	#include "atmel_start.h"
}

#include "drivers/CRTC.h"

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
	// Don't do this because we don't want to use the buck converter because of the inductor requirement. Stay on LDO.
	/* 1. Set buck regulator as Main Voltage Regulator */
	// SUPC->VREG.bit.SEL = 1;
	// while(SUPC->STATUS.bit.VCORERDY != 1);

	// Won't need to do this since we are using RTC, not sercom
	/* 2. Enable dynamic power domain gating for PD0/1 */
	// PM->STDBYCFG.bit.DPGPD0 = 1;
	// PM->STDBYCFG.bit.DPGPD1 = 1;

	/* 3. Enable VREG to run on demand */
	//SUPC->VREG.bit.RUNSTDBY = 1;

	// On the L21B, set lpeff to 1 for more efficiency
	#ifndef SAM_L21_REV_A
	//SUPC->VREG.bit.LPEFF    = 1;
	#endif

	/* 4. Set STANDBY as sleep mode */
	PM->SLEEPCFG.reg = PM_SLEEPCFG_SLEEPMODE_STANDBY;
	while (PM->SLEEPCFG.reg != PM_SLEEPCFG_SLEEPMODE_STANDBY);
}

#include "drivers/Port.hpp"

typedef port::CDigitalPin< port::PORTB, 10 > led;

int main(void)
{
	CRTC rtc;

	// Chip and peripheral initialization
	system_init();	

	rtc.Initialize();

	// Program Init
	/** Set STANDBY as sleep mode */
	demo_set_sleepmode_STANDBY();

	// Always set input pins to be pullup enabled to avoid additional power draw
	gpio_set_pin_pull_mode(SW0,	GPIO_PULL_UP);

	int count = 3;

	// Program loop
	// Blink LED
	while(1)	
	{
		if( count != 0 )
		{
			led::Set();
			delay_ms(500);
			led::Clear();
			delay_ms(500);

			count--;
		}
		else
		{
			// Enable the RTC interrupt to wake up in 5 secs
			rtc.EnableInterrupt();

			// Enter sleep mode
			demo_system_sleep();

			// On wakeup, disable the RTC interrupt
			// Enable the RTC interrupt to wake up in 5 secs
			rtc.DisableInterrupt();

			// Wait 2 seconds before starting LED flash again
			delay_ms(2000);

			// Set the counter back to 3
			count = 3;
		}
	}
}
