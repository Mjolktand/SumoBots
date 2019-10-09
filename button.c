#include <avr/io.h>

#include "led.h"

void button_init()
{
	DDRD &= ~(1 << DDD2);
}

uint8_t button_logic_start()
{
	static uint8_t button_status = 0;

	if (PIND & (1 << PIND2))
	{
		button_status = 1;
		led_2_on();
	}
	else if (!(PIND & (1 << PIND2)) && button_status == 1)
	{
		button_status = 0;
		led_1_off();
		return 1;
	}
	return 0;
}

uint8_t button_logic_stop()
{
	static uint8_t button_status = 0;

	if (PIND & (1 << PIND2))
	{
		button_status = 1;
		led_1_on();
	}
	else if (!(PIND & (1 << PIND2)) && button_status == 1)
	{
		button_status = 0;
		led_2_off();
		return 1;
	}
	return 0;
}
