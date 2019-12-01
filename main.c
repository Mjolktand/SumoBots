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
#include "button.h"

#define BOT2

#ifdef BOT1
	#include "bot_logic.h"
#endif

#ifdef BOT2
	#include "bot2_logic.h"
#endif

void main (void)
{
	sei();
	uart_init();

	#ifdef BOT1
		bot_init();
	#endif
	#ifdef BOT2
		bot2_init();
	#endif

	while(1)
	{
		if (button_logic_start())
		{
			#ifdef BOT1
				bot_instructions();
			#endif
			#ifdef BOT2
				bot2_instructions();
			#endif
		}
	}
}

#ifdef BOT1
	ISR (TIMER1_COMPA_vect)
	{
		timer_counter++;
		if(timer_counter >= 50000)
		{
			timer_counter = 0;
		}
	}
#endif

#ifdef BOT2
	ISR (TIMER1_COMPA_vect)
	{
		timer_counter2++;
		if(timer_counter2 >= 50000)
		{
			timer_counter2 = 0;
		}
	}
#endif
