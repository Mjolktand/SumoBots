#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "serial.h"
#include "timer.h"
#include "util.h"
#include "motors.h"
#include "linesensor.h"
#include "rangesensor.h"
#include "bot_logic.h"




void main (void)
{
	//sei();
	uart_init();
	linesens_init();
	//motors_init();
	//timer1_start();
	//bot_instructions();

	while(1){
		linesens_read();
		linesens_print_values();
		_delay_ms(1000);
	}
}



ISR (TIMER1_COMPA_vect)
{
	 printf("checking sensor.. \n");
	 linesens_read();
	 linesens_print_values();
	 if(linesens_check_results())
	 {
		 printf("Line detected!! \n");
		 alert = 1;
		 instruction = 1;
	 }
	 timer_counter++;
	 if(timer_counter >= 50000)
	 {
		 timer_counter = 0;
	 }
}
