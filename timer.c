#include <avr/io.h>
#include "timer.h"

void timer1_start()
{
  TCCR1B |= (1 << WGM12);
  OCR1A = 155;
  TIMSK1 |= (1 << OCIE1A); //compare match A interrupt
  TCCR1B  |= (1 << CS12) | (1 << CS10);
}

void timer0_stop()
{
  TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
  TIFR0 |= (1 << OCF0A);
}

void timer0_start_2500us()
{
  TCCR0A |= (1 << WGM01);
  OCR0A = 155;
  TCCR0B |= (1 << CS02); //starts 2500us timer (16 us per tick)
}

void timer0_delay_10us()
{
//set CTC mode
  TCCR0A |= (1 << WGM01);
  OCR0A = 19;
//set prescaler to 8
  TCCR0B |= (1 << CS01);
  while (!(TIFR0 & (1 << OCF0A)))
	{
    ;
	}
  timer0_stop();
}
