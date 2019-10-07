#include <avr/io.h>

void rangesensor_init()
{
	DDRC |= (1 << DDC1);
	DDRC &= ~(1 << DDC0);
}

uint8_t rangesensor_read_cm()
{
	uint8_t range_value;
	PORTC |= (1 << PORTC1);
//10us delay
	PORTC &= ~(1 << PORTC1);
//start clock
	while (!(TIFR0 & (1 << OCF0A)))
	{
		if (!(PINC & (1 << PINC0)))
		{
			range_value = TCNT0;
		}
	}
//stop clock
	return range_value * 10 / 58;
}
