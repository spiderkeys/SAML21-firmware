/**
 * \file
 *
 * \brief ADC functionality declaration.
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

#ifndef HAL_ADC_ASYNC_H_INCLUDED
#define HAL_ADC_ASYNC_H_INCLUDED

#include <hpl_adc_async.h>
#include <utils_ringbuffer.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup hal_adc_async ADC Driver
 *
 * \section adc_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

/**
 * \brief ADC descriptor
 *
 * The ADC descriptor forward declaration.
 */
struct adc_async_descriptor;

/**
 * \brief ADC callback type
 */
typedef void (* adc_async_cb_t)(const struct adc_async_descriptor *const descr);

/**
 * \brief ADC callback types
 */
enum adc_async_callback_type {
	ADC_ASYNC_CONVERT_CB,
	ADC_ASYNC_MONITOR_CB,
	ADC_ASYNC_ERROR_CB
};

/**
 * \brief ADC callbacks
 */
struct adc_async_callbacks {
	adc_async_cb_t convert_done;
	adc_async_cb_t monitor;
	adc_async_cb_t error;
};

/**
 * \brief ADC descriptor
 */
struct adc_async_descriptor {
	struct _adc_async_device device;
	struct adc_async_callbacks adc_async_cb;
	struct ringbuffer convert;
	uint16_t bytes_in_buffer;
};

/**
 * \brief Initialize ADC
 *
 * This function initializes the given ADC descriptor.
 * It checks if the given hardware is not initialized and if the given hardware
 * is permitted to be initialized.
 *
 * \param[out] descr An ADC descriptor to initialize
 * \param[in] hw The pointer to hardware instance
 * \param[in] convert_buffer A buffer to keep converted values
 * \param[in] convert_buffer_length The length of the buffer above
 *
 * \return Initialization status.
 * \retval -1 Passed parameters were invalid or an ADC is already initialized
 * \retval 0 The initialization is completed successfully
 */
int32_t adc_async_init(struct adc_async_descriptor *const descr, void *const hw,
		uint8_t *const convert_buffer, const uint16_t convert_buffer_length);

/**
 * \brief De-initialize ADC
 *
 * This function de-initializes the given ADC descriptor.
 * It checks if the given hardware is initialized and if the given hardware is
 * permitted to be de-initialized.
 *
 * \param[in] descr An ADC descriptor to de-initialize
 *
 * \return De-initialization status.
 */
int32_t adc_async_deinit(struct adc_async_descriptor *const descr);

/**
 * \brief Enable ADC
 *
 * Use this function to set the ADC peripheral to enabled state
 *
 * \param[in] descr An ADC descriptor
 *
 * \return Operation status
 *
 */
int32_t adc_async_enable(struct adc_async_descriptor *const descr);

/**
 * \brief Disable ADC
 *
 * Use this function to set the ADC peripheral to disabled state
 *
 * \param[in] descr An ADC descriptor
 *
 * \return Operation status
 *
 */
int32_t adc_async_disable(struct adc_async_descriptor *const descr);

/**
 * \brief Register ADC callback
 *
 * \param[in] io_descr An adc descriptor
 * \param[in] type Callback type
 * \param[in] cb A callback function, passing NULL de-registers callback
 *
 * \return The status of callback assignment.
 * \retval -1 Passed parameters were invalid or the adc is not initialized
 * \retval 0 A callback is registered successfully
 */
int32_t adc_async_register_callback(struct adc_async_descriptor *const descr,
		const enum adc_async_callback_type type, adc_async_cb_t cb);

/*
 * \brief Read data from ADC
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] buf A buffer to read data to
 * \param[in] length The size of a buffer
 *
 * \return The number of bytes read.
 */
int32_t adc_async_read(struct adc_async_descriptor *const descr,
		uint8_t *const buffer, const uint16_t length);

/**
 * \brief Start conversion
 *
 * This function starts single conversion if no automatic (free-run) mode is
 * enabled.
 *
 * \param[in] descr The pointer to ADC descriptor
 *
 * \return Start conversion status.
 */
int32_t adc_async_start_conversion(struct adc_async_descriptor *const descr);

/**
 * \brief Set ADC reference source
 *
 * This function sets ADC reference source.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] reference A reference source to set
 *
 * \return Status of ADC reference source setting.
 */
int32_t adc_async_set_reference(struct adc_async_descriptor *const descr,
		const adc_reference_t reference);

/**
 * \brief Set ADC resolution
 *
 * This function sets ADC resolution.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] resolution A resolution to set
 *
 * \return Status of ADC resolution setting.
 */
int32_t adc_async_set_resolution(struct adc_async_descriptor *const descr,
		const adc_resolution_t resolution);

/**
 * \brief Set ADC channels
 *
 * This function sets ADC positive and negative channels.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] pos_channel A positive channels to set
 * \param[in] neg_channel A negative channels to set
 *
 * \return Status of ADC channels setting.
 */
int32_t adc_async_set_channels(struct adc_async_descriptor *const descr,
		const adc_pos_channel_t pos_channel,
		const adc_neg_channel_t neg_channel);

/**
 * \brief Set ADC thresholds
 *
 * This function sets ADC positive and negative thresholds.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] low_threshold A lower thresholds to set
 * \param[in] up_threshold An upper thresholds to set
 *
 * \return Status of ADC thresholds setting.
 */
int32_t adc_async_set_thresholds(struct adc_async_descriptor *const descr,
		const adc_threshold_t low_threshold,
		const adc_threshold_t up_threshold);

/**
 * \brief Set ADC gain
 *
 * This function sets ADC gain.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] gain A gain to set
 *
 * \return Status of ADC gain setting.
 */
int32_t adc_async_set_gain(struct adc_async_descriptor *const descr,
		const adc_gain_t gain);

/**
 * \brief Set ADC conversion mode
 *
 * This function sets ADC conversion mode.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] mode A conversion mode to set
 *
 * \return Status of ADC conversion mode setting.
 */
int32_t adc_async_set_conversion_mode(struct adc_async_descriptor *const descr,
		const enum adc_conversion_mode mode);

/**
 * \brief Set ADC differential mode
 *
 * This function sets ADC differential mode.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] mode A differential mode to set
 *
 * \return Status of ADC differential mode setting.
 */
int32_t adc_async_set_differential_mode(struct adc_async_descriptor *const descr,
		const enum adc_differential_mode mode);

/**
 * \brief Set ADC window mode
 *
 * This function sets ADC window mode.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[in] mode A window mode to set
 *
 * \return Status of ADC window mode setting.
 */
int32_t adc_async_set_window_mode(struct adc_async_descriptor *const descr,
		const adc_window_mode_t mode);

/**
 * \brief Retrieve threshold state
 *
 * This function retrieves ADC threshold state.
 *
 * \param[in] descr The pointer to ADC descriptor
 * \param[out] state The threshold state
 *
 * \return The state of ADC thresholds state retrieving.
 */
int32_t adc_async_get_threshold_state(
		const struct adc_async_descriptor *const descr,
		adc_threshold_status_t *const state);

/**
 * \brief Check if conversion is complete
 *
 * This function checks if ADC has finished the conversion.
 *
 * \param[in] descr The pointer to ADC descriptor
 *
 * \return The status of ADC conversion completion checking.
 * \retval 1 The conversion is complete
 * \retval 0 The conversion is not complete
 */
int32_t adc_async_is_conversion_complete(
		const struct adc_async_descriptor *const descr);

/**
 * \brief flush adc ringbuf
 *
 * This function flush adc rx ringbuf. 
 *
 * \param[in] descr The pointer to ADC descriptor
 *
 * \return ERR_NONE 
 */
int32_t adc_async_flush_rx_buffer(struct adc_async_descriptor *const descr);

/**
 * \brief Retrieve the current driver version
 *
 * \return Current driver version
 */
uint32_t adc_async_get_version(void);
/**@}*/

#ifdef __cplusplus
}
#endif

#include <hpl_missing_features.h>

#endif /* HAL_ADC_ASYNC_H_INCLUDED */
