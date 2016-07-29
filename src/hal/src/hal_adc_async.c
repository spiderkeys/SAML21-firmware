/**
 * \file
 *
 * \brief ADC functionality implementation.
 *
 * Copyright (C) 2015-2016 Atmel Corporation. All rights reserved.
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

/**
 * \brief Indicates HAL being compiled. Must be defined before including.
 */
#define _COMPILING_HAL

#include "hal_adc_async.h"
#include <utils_assert.h>
#include <utils.h>
#include <hal_atomic.h>

/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

static void adc_async_conversion_done(struct _adc_async_device *device,
		const uint16_t data);
static void adc_async_window_threshold_reached(struct _adc_async_device *device);
static void adc_async_error_occured(struct _adc_async_device *device);

/**
 * \brief Initialize ADC
 */
int32_t adc_async_init(struct adc_async_descriptor *const descr, void *const hw,
		uint8_t *const convert_buffer, const uint16_t convert_buffer_length)
{
	int32_t init_status;
	struct _adc_async_device *device;

	ASSERT(descr && hw && convert_buffer && convert_buffer_length);

	descr->bytes_in_buffer = 0;
	if (ERR_NONE != ringbuffer_init(&descr->convert, convert_buffer,
			convert_buffer_length)) {
		return ERR_INVALID_ARG;
	}

	device = &descr->device;
	init_status = _adc_async_init(device, hw);
	if (init_status) {
		return init_status;
	}

	device->adc_async_cb.convert_done = adc_async_conversion_done;
	device->adc_async_cb.window_cb = adc_async_window_threshold_reached;
	device->adc_async_cb.error_cb = adc_async_error_occured;

	return ERR_NONE;
}

/**
 * \brief De-initialize ADC
 */
int32_t adc_async_deinit(struct adc_async_descriptor *const descr)
{
	ASSERT(descr);

	_adc_async_deinit(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Enable ADC
 */
int32_t adc_async_enable(struct adc_async_descriptor *const descr)
{
	ASSERT(descr);

	_adc_async_enable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Disable ADC
 */
int32_t adc_async_disable(struct adc_async_descriptor *const descr)
{
	ASSERT(descr);

	_adc_async_disable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Register ADC callback
 */
int32_t adc_async_register_callback(struct adc_async_descriptor *const descr,
		const enum adc_async_callback_type type, adc_async_cb_t cb)
{
	ASSERT(descr);

	switch (type) {
	case ADC_ASYNC_CONVERT_CB:
		descr->adc_async_cb.convert_done = cb;
		break;
	case ADC_ASYNC_MONITOR_CB:
		descr->adc_async_cb.monitor = cb;
		break;
	case ADC_ASYNC_ERROR_CB:
		descr->adc_async_cb.error = cb;
		break;
	default:
		return ERR_INVALID_ARG;
	}

	_adc_async_set_irq_state(&descr->device, (enum _adc_async_callback_type)type,
			cb != NULL);

	return ERR_NONE;
}

/*
 * \brief Read data from ADC
 */
int32_t adc_async_read(struct adc_async_descriptor *const descr,
		uint8_t *const buffer, const uint16_t length)
{
	uint8_t data_size;
	uint32_t num;
	uint16_t was_read = 0;

	ASSERT(descr && buffer && length);

	data_size = _adc_async_get_data_size(&descr->device);
	ASSERT(!(length % data_size));
	(void)data_size;

	CRITICAL_SECTION_ENTER()
	num = ringbuffer_num(&descr->convert);
	CRITICAL_SECTION_LEAVE()

	while ((was_read < num) && (was_read < length)) {
		ringbuffer_get(&descr->convert, &buffer[was_read++]);
	}
	descr->bytes_in_buffer -= was_read;

	return was_read;
}

/**
 * \brief Start conversion
 */
int32_t adc_async_start_conversion(struct adc_async_descriptor *const descr)
{
	ASSERT(descr);

	_adc_async_convert(&descr->device);
	return ERR_NONE;
}

/**
 * \brief Set ADC reference source
 */
int32_t adc_async_set_reference(struct adc_async_descriptor *const descr,
		const adc_reference_t reference)
{
	ASSERT(descr);

	_adc_async_set_reference_source(&descr->device, reference);
	return ERR_NONE;
}

/**
 * \brief Set ADC resolution
 */
int32_t adc_async_set_resolution(struct adc_async_descriptor *const descr,
		const adc_resolution_t resolution)
{
	ASSERT(descr);

	_adc_async_set_resolution(&descr->device, resolution);
	return ERR_NONE;
}

/**
 * \brief Set ADC channels
 */
int32_t adc_async_set_channels(struct adc_async_descriptor *const descr,
		const adc_pos_channel_t pos_channel,
		const adc_neg_channel_t neg_channel)
{
	ASSERT(descr);

	_adc_async_set_pos_channel(&descr->device, pos_channel);
	_adc_async_set_neg_channel(&descr->device, neg_channel);
	return ERR_NONE;
}

/**
 * \brief Set ADC thresholds
 */
int32_t adc_async_set_thresholds(struct adc_async_descriptor *const descr,
		const adc_threshold_t low_threshold,
		const adc_threshold_t up_threshold)
{
	ASSERT(descr);

	_adc_async_set_low_threshold(&descr->device, low_threshold);
	_adc_async_set_up_threshold(&descr->device, up_threshold);
	return ERR_NONE;
}

/**
 * \brief Set ADC gain
 */
int32_t adc_async_set_gain(struct adc_async_descriptor *const descr,
		const adc_gain_t gain)
{
	ASSERT(descr);

	_adc_async_set_gain(&descr->device, gain);
	return ERR_NONE;
}

/**
 * \brief Set ADC conversion mode
 */
int32_t adc_async_set_conversion_mode(struct adc_async_descriptor *const descr,
		const enum adc_conversion_mode mode)
{
	ASSERT(descr);

	_adc_async_set_conversion_mode(&descr->device, mode);
	return ERR_NONE;
}

/**
 * \brief Set ADC differential mode
 */
int32_t adc_async_set_differential_mode(struct adc_async_descriptor *const descr,
		const enum adc_differential_mode mode)
{
	ASSERT(descr);

	_adc_async_set_differential_mode(&descr->device, mode);
	return ERR_NONE;
}

/**
 * \brief Set ADC window mode
 */
int32_t adc_async_set_window_mode(struct adc_async_descriptor *const descr,
		const adc_window_mode_t mode)
{
	ASSERT(descr);

	_adc_async_set_window_mode(&descr->device, mode);
	return ERR_NONE;
}

/**
 * \brief Retrieve threshold state
 */
int32_t adc_async_get_threshold_state(
		const struct adc_async_descriptor *const descr,
		adc_threshold_status_t *const state)
{
	ASSERT(descr && state);

	_adc_async_get_threshold_state(&descr->device, state);
	return ERR_NONE;
}

/**
 * \brief Check if conversion is complete
 */
int32_t adc_async_is_conversion_complete(
		const struct adc_async_descriptor *const descr)
{
	ASSERT(descr);

	return _adc_async_is_conversion_done(&descr->device);
}

/**
 * \brief flush adc ringbuf
 */
int32_t adc_async_flush_rx_buffer(struct adc_async_descriptor *const descr)
{
	ASSERT(descr);

	return ringbuffer_flush(&descr->convert);
}

/**
 * \brief Retrieve the current driver version
 */
uint32_t adc_async_get_version(void)
{
	return DRIVER_VERSION;
}

/**
 * \internal Process conversion completion
 *
 * \param[in] device The pointer to ADC device structure
 * \param[in] data Converted data
 */
static void adc_async_conversion_done(struct _adc_async_device *device,
		const uint16_t data)
{
	struct adc_async_descriptor *const descr = CONTAINER_OF(device,
		struct adc_async_descriptor, device);

	ringbuffer_put(&descr->convert, data);
	if (1 < _adc_async_get_data_size(&descr->device)) {
		ringbuffer_put(&descr->convert, data >> 8);
		++descr->bytes_in_buffer;
	}
	++descr->bytes_in_buffer;

	if (descr->adc_async_cb.convert_done) {
		descr->adc_async_cb.convert_done(descr);
	}
}

static void adc_async_window_threshold_reached(struct _adc_async_device *device)
{
	struct adc_async_descriptor *const descr = CONTAINER_OF(device,
		struct adc_async_descriptor, device);

	if (descr->adc_async_cb.monitor) {
		descr->adc_async_cb.monitor(descr);
	}
}

static void adc_async_error_occured(struct _adc_async_device *device)
{
	struct adc_async_descriptor *const descr = CONTAINER_OF(device,
		struct adc_async_descriptor, device);

	if (descr->adc_async_cb.error) {
		descr->adc_async_cb.error(descr);
	}
}

//@}
