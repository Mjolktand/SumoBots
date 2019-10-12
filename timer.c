#include <avr/io.h>
#include "timer.h"

void timer1_init()
{
	//setting interrupt timer to 10 ms
  TCCR1B |= (1 << WGM12);
  OCR1A = 155;
  TIMSK1 |= (1 << OCIE1A);
  TCCR1B  |= (1 << CS12) | (1 << CS10);
}

void timer0_stop()
{
  TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
  TIFR0 |= (1 << OCF0A);
}

void timer0_start_2500us()
{
	//starts 2500us timer (16 us per tick)
  TCCR0A |= (1 << WGM01);
  OCR0A = 155;
  TCCR0B |= (1 << CS02);
}

void timer0_delay_10us()
{
  TCCR0A |= (1 << WGM01);
  OCR0A = 19;
  TCCR0B |= (1 << CS01);
  while (!(TIFR0 & (1 << OCF0A)))
	{
    ;
	}
  timer0_stop();
}
