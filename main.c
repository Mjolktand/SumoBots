#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>

#include "gpio.h"
#include "serial.h"
#include "timer.h"
#include "util.h"
#include "motors.h"
#include "bot_logic.h" //use for first bot
//#include "bot2_logic.h" //use for second bot
#include "button.h"

void main (void)
{
	sei();
	bot_init(); //use for first bot
	//bot2_init(); //use for second bot
	uart_init();

	while(1)
	{
		if (button_logic_start())
		{
			bot_instructions(); //use for first bot
			//bot2_instructions(); //use for second bot
		}
	}
}

//use for first bot
ISR (TIMER1_COMPA_vect)
{
	timer_counter++;
	if(timer_counter >= 50000)
	{
		timer_counter = 0;
	}
}

//use for second bot
/*ISR (TIMER1_COMPA_vect)
{
	timer_counter2++;
	if(timer_counter2 >= 50000)
	{
		timer_counter2 = 0;
	}
}*/
