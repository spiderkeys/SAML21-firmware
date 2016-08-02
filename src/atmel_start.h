/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_H_INCLUDED
#define ATMEL_START_H_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
		extern "C" {
#endif

#include <hal_usart_async.h>
#include <hal_spi_m_sync.h>
#include <hal_timer.h>
#include <hpl_tc2_v200_base.h>

#include <hal_adc_sync.h>

#include <hal_delay.h>

	extern struct usart_async_descriptor EDBG_COM;
	extern struct spi_m_sync_descriptor EDBG_SPI;
	extern struct timer_descriptor TIMER_0;

	extern struct adc_sync_descriptor ADC_0;

	void EDBG_COM_PORT_init(void);
	void EDBG_COM_CLOCK_init(void);
	void EDBG_COM_init(void);
	void EDBG_COM_example(void);

	void EDBG_SPI_PORT_init(void);
	void EDBG_SPI_CLOCK_init(void);
	void EDBG_SPI_init(void);
	void EDBG_SPI_example(void);

	void ADC_0_PORT_init(void);
	void ADC_0_CLOCK_init(void);
	void ADC_0_init(void);
	void ADC_0_example(void);

	void RTC_Init();
	void RTC_EnableInterrupt();
	void RTC_DisableInterrupt();

	void delay_driver_init(void);
	void delay_example(void);

	/**
	 * \brief Perform system initialization, initialize pins and clocks for
	 * peripherals
	 */
	void system_init(void);

#ifdef __cplusplus
		}
#endif
#endif // ATMEL_START_H_INCLUDED
