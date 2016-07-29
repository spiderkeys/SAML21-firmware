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
#include <hal_timer.h>
#include <hpl_tc2_v200_base.h>
#include <hal_adc_async.h>

	extern struct usart_async_descriptor EDBG_COM;
	extern struct timer_descriptor TIMER_0;
	extern struct adc_async_descriptor IO1_LIGHT_SENS;

	void EDBG_COM_PORT_init(void);
	void EDBG_COM_CLOCK_init(void);
	void EDBG_COM_init(void);
	void EDBG_COM_example(void);

	/**
	 * \brief Perform system initialization, initialize pins and clocks for
	 * peripherals
	 */
	void system_init(void);

#ifdef __cplusplus
		}
#endif
#endif // ATMEL_START_H_INCLUDED
