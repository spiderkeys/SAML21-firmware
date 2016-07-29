// extern "C"
// {
// 	#include "atmel_start.h"
// }

// #define MAX_TIMER_FIRE_AMOUNT 32

// enum app_state {
// 	APP_STATE_WAITING_FOR_WELCOMING_STR_TX,
// 	APP_STATE_WAITING_FOR_TIMER,
// 	APP_STATE_WAITING_FOR_COLLECT_STR_TX,
// 	APP_STATE_WAITING_FOR_DOT_STR_TX,
// 	APP_STATE_WAITING_FOR_SENSOR_VALUE_STR_TX,
// 	APP_STATE_WAITING_FOR_SENSOR_VALUE_TX,
// 	APP_STATE_WAITING_FOR_NEW_LINE_STR,
// 	APP_STATE_WAITING_FOR_ADC_CONVERSION,
// 	APP_STATE_WAITING_FOR_USART_TX,
// };

// static struct timer_task task;
// static enum app_state state;
// static uint8_t fired_count;
// static struct io_descriptor *io;
// static uint8_t adc_values[MAX_TIMER_FIRE_AMOUNT];
// static uint16_t average_adc_value;

// static const uint8_t sensor_value_str[] = "\r\nAverage light sensor value is 0x";
// static const uint8_t new_line_str[] = "\r\n";
// static const uint8_t welcoming_str[] = "Welcome to Light Sensor example \
// application.\r\nThis applications periodically reads value from light \
// sensor and writes to USART console.\r\n";
// static const uint8_t collect_str[] = "Collecting data from the light sensor.";
// static const uint8_t dot_str[] = ".";

// static const uint8_t hex[] = "01234567890abcdef";
// static uint8_t sensor_value[2];

// /**
//  * \brief ADC callback about conversion completion
//  *
//  * \param[in] descr The pointer to corresponding ADC descriptor
//  */
// static void adc_cb(const struct adc_async_descriptor *const descr)
// {
// 	adc_async_read(&IO1_LIGHT_SENS, &adc_values[fired_count - 1], 1);
// 	state = APP_STATE_WAITING_FOR_TIMER;
// 	timer_add_task(&TIMER_0, &task);
// }

// /**
//  * \brief USART callback about transmission completion
//  *
//  * \param[in] descr The pointer to corresponding USART descriptor
//  */
// static void usart_tx_cb(const struct usart_async_descriptor *const descr)
// {
// 	if ((APP_STATE_WAITING_FOR_WELCOMING_STR_TX == state) ||
// 				(APP_STATE_WAITING_FOR_NEW_LINE_STR == state)) {
// 		state = APP_STATE_WAITING_FOR_TIMER;
// 		timer_add_task(&TIMER_0, &task);

// 	 } else if (APP_STATE_WAITING_FOR_SENSOR_VALUE_STR_TX == state) {
// 		 state = APP_STATE_WAITING_FOR_SENSOR_VALUE_TX;
// 		 sensor_value[0] = hex[(average_adc_value & 0xf0) >> 4];
// 		 sensor_value[1] = hex[average_adc_value & 0x0f];
// 		 io_write(io, sensor_value, 2);

// 	 } else if (APP_STATE_WAITING_FOR_SENSOR_VALUE_TX == state) {
// 		 state = APP_STATE_WAITING_FOR_NEW_LINE_STR;
// 		 io_write(io, new_line_str, sizeof(new_line_str) - 1);

// 	 } else if (APP_STATE_WAITING_FOR_COLLECT_STR_TX == state ||
// 	 			APP_STATE_WAITING_FOR_DOT_STR_TX == state) {
// 	 	state = APP_STATE_WAITING_FOR_ADC_CONVERSION;
// 		adc_async_start_conversion(&IO1_LIGHT_SENS);
// 	 }
// }

// /**
//  * \brief Timer task callback
//  *
//  * \param[in] descr The pointer to corresponding task
//  */
// void timer_cb(const struct timer_task *const timer_task)
// {
// 	fired_count++;

// 	if (1 == fired_count) {
// 		state = APP_STATE_WAITING_FOR_COLLECT_STR_TX;
// 		io_write(io, collect_str, sizeof(collect_str) - 1);

// 	} else if (fired_count == MAX_TIMER_FIRE_AMOUNT) {
// 		uint8_t i = 0;

// 		fired_count = 0;
// 		average_adc_value = 0;

// 		for (; i < MAX_TIMER_FIRE_AMOUNT; i++) {
// 			average_adc_value += adc_values[i];
// 		}
// 		average_adc_value /= MAX_TIMER_FIRE_AMOUNT;

// 		state = APP_STATE_WAITING_FOR_SENSOR_VALUE_STR_TX;
// 		io_write(io, sensor_value_str, sizeof(sensor_value_str) - 1);

// 		return;

// 	} else {
// 		state = APP_STATE_WAITING_FOR_DOT_STR_TX;
// 		io_write(io, dot_str, sizeof(dot_str) - 1);
// 	}
// }

int main(void)
{
	// system_init();

	// task.cb = timer_cb;
	// task.interval = 250;
	// task.mode = TIMER_TASK_ONE_SHOT;

	// adc_async_register_callback(&IO1_LIGHT_SENS, ADC_ASYNC_CONVERT_CB, adc_cb);
	// adc_async_enable(&IO1_LIGHT_SENS);

	// timer_start(&TIMER_0);

	// usart_async_register_callback(&EDBG_COM, USART_ASYNC_TXC_CB, usart_tx_cb);
	// usart_async_get_io_descriptor(&EDBG_COM, &io);
	// usart_async_enable(&EDBG_COM);
	// state = APP_STATE_WAITING_FOR_WELCOMING_STR_TX;
	// io_write(io, welcoming_str, sizeof(welcoming_str) - 1);

	while(1) {
	};
}
