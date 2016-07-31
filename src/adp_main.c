/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */
#include "atmel_start.h"
#include <hal_gpio.h>
#include "adp_main.h"

struct adp_msg_request_handshake ATMEL_DATA_PROTOCOL_0_desc;

void ATMEL_DATA_PROTOCOL_0_init(void)
{
	adp_init();
}

/* Example stream id */
#define STREAM_ID_STATUS_MESSAGE       0x00

/* Received the packet data buffer */
uint8_t recv_pkg[MSG_RES_PACKET_DATA_MAX_LEN] = {0, };

/* Terminal configuration. Global, so we can change it later */
struct adp_msg_conf_terminal terminal_config = {
	.terminal_id = 0,
	.width = 80,
	.height = 50,
	.background_color = {ADP_COLOR_WHITE},
	.foreground_color = {ADP_COLOR_GREEN}
};
void ATMEL_DATA_PROTOCOL_0_example(void)
{
	struct adp_msg_configure_stream stream;

	while (adp_wait_for_handshake() != ADP_HANDSHAKE_ACCEPTED) {
	}

	adp_configure_info("ADP Hellow world Example for Xplained Pro",
			"This example demonstrates how to use ADP terminal component");

	/* Add terminal stream */
	stream.stream_id = STREAM_ID_STATUS_MESSAGE;
	stream.type = ADP_STREAM_UINT_8;
	stream.mode = ADP_STREAM_OUT;
	stream.state = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Status messages");

	adp_configure_terminal(&terminal_config, "Status terminal");

	/* Connect stream and terminal */
	struct adp_msg_add_stream_to_terminal terminal_stream = {
		.terminal_id = 0,
		.stream_id = STREAM_ID_STATUS_MESSAGE,
		.mode = 0xFF,
		.text_color = {ADP_COLOR_BLACK},
		.tag_text_color = {ADP_COLOR_WHITE}
	};
	adp_add_stream_to_terminal(&terminal_stream, "Status messages");

	adp_transceive_single_stream(STREAM_ID_STATUS_MESSAGE,
			(uint8_t *)"Hello ADP!", 10, recv_pkg);
}

void adp_app_init(void)
{
	ATMEL_DATA_PROTOCOL_0_init();
	/* Pass SPI SS pin to init when use SPI interface */
	/* adp_spi_interface_init(&EDBG_SPI.io, EDBG_SPI_SS_PIN); */
}
