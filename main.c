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
#include "motors.h"

#include "bot2_logic.h"
#include "button.h"

void main (void)
{
	sei();
	bot2_init(); //bot2_init for the second bot
	uart_init();

	while(1)
	{
		if (button_logic_start())
		{
			bot2_instructions(); //bot2_logic for the second bot
		}
	}
}

ISR (TIMER1_COMPA_vect)
{
	timer_counter2++;
	if(timer_counter2 >= 50000)
	{
		timer_counter2 = 0;
	}
}
