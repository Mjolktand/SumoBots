#include <avr/io.h>

void led_init()
{
	DDRC |= (1 << DDC2) | (1 << DDC3);
}

void led_1_on()
{
	PORTC |= (1 << PORTC2);
}

void led_1_off()
{
	PORTC &= ~(1 << PORTC2);
}

void led_2_on()
{
	PORTC |= (1 << PORTC3);
}

void led_2_off()
{
	PORTC &= ~(1 << PORTC3);
}
