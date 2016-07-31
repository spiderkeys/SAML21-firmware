/**
 * \file
 *
 * \brief ADP service implementation
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include <compiler.h>
#include <hal_gpio.h>
#include <hal_io.h>
#include <adp_interface.h>

static struct io_descriptor *io;
static uint8_t DGI_SS_PIN = 0xFF;
enum adp_interface_type {
	ADP_INTERFACE_SPI,
	ADP_INTERFACE_I2C,
	ADP_INTERFACE_GPIO
};
static enum adp_interface_type dgi_type;
/**
 * * \brief Send SPI start condition
 * *
 * */
static inline void adp_interface_send_start(void)
{
	if (dgi_type == ADP_INTERFACE_SPI) {
		/* Send SPI start condition */
		gpio_set_pin_level(DGI_SS_PIN , false);
	}
}

/**
 * * \brief Send SPI stop condition
 * *
 * */
static inline void adp_interface_send_stop(void)
{
	if (dgi_type == ADP_INTERFACE_SPI) {
		/* Send SPI end condition */
		gpio_set_pin_level(DGI_SS_PIN , true);
	}
	
}

/**
 * \brief Initialize ADP SPI interface
 *
 */
void adp_interface_init_spi(struct io_descriptor *io_descr, const uint8_t ss_pin)
{
	io = io_descr;
	dgi_type = ADP_INTERFACE_SPI;
	DGI_SS_PIN = ss_pin;
}

/**
 * \brief Initialize ADP I2C interface
 *
 */
void adp_interface_init_i2c(struct io_descriptor *io_descr)
{
	io = io_descr;
	dgi_type = ADP_INTERFACE_I2C;
}

/**
 * * \brief Sends and reads protocol packet data byte on SPI
 * *
 * * \param[in]  tx_buf  Pointer to send the protocol packet data
 * * \param[in]  length  The length of the send protocol packet data
 * * \param[out] rx_buf  Pointer to store the received SPI character
 * */
void adp_interface_transceive_procotol(uint8_t* tx_buf, uint16_t length, uint8_t* rx_buf)
{
	(void) rx_buf;

	adp_interface_send_start();

	io_write(io, tx_buf, length);

	adp_interface_send_stop();
}

/**
 * * \brief Read response on SPI from PC
 * *
 * * return Status
 * * \param[in]  rx_buf  Pointer to receive the data
 * * \param[in]  length  The length of the read data
 * * \param[out] rx_buf  Pointer to store the received SPI character
 * */
bool adp_interface_read_response(uint8_t* rx_buf, uint16_t length)
{
	bool status = false;

	adp_interface_send_start();	

	io_read(io, rx_buf, length);

	adp_interface_send_stop();

	return status;
}
