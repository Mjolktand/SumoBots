#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "gpio.h"
#include "serial.h"
#include "timer.h"
#include "util.h"

#include "bot_logic.h"
#include "button.h"

void main (void)
{
	sei();
	bot_init(); //bot2_init for the second bot

	while(1)
	{
		if (button_logic_start())
		{
			bot_instructions(); //bot2_logic for the second bot
		}
	}
}

ISR (TIMER1_COMPA_vect)
{
	timer_counter++;
	if(timer_counter >= 50000)
	{
		timer_counter = 0;
	}
}
