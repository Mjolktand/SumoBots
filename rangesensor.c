#include <avr/io.h>

#include "timer.h"

void rangesensor_init()
{
	DDRC |= (1 << DDC1);
	DDRC &= ~(1 << DDC0);
}

uint8_t rangesensor_read()
{
	uint8_t range_value;
	PORTC |= (1 << PORTC1);
	timer0_delay_10us();
	PORTC &= ~(1 << PORTC1);
	timer0_start_2500us();
	while (!(TIFR0 & (1 << OCF0A)))
	{
		if (PINC & (1 << PINC0))
		{
			range_value = TCNT0;
		}
	}
	timer0_stop();

	//valid range return 1 to 155;
	return range_value;
}
