#include "atmel_start.h"
#include <hal_gpio.h>
#include <hal_delay.h>


int main(void)
{
	system_init();

	while (true) {
		delay_ms(5000);
		gpio_toggle_pin_level(LED0);
	}
}
