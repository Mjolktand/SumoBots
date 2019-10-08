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

void main (void)
{
	uart_init();
	linesens_init();
	uint8_t *korv;
	while(1){
		korv = linesens_read();
		printf("value 1: %d value 2: %d \n",korv[0], korv[5]);
		_delay_ms(1000);
	}
}


ISR (TIMER1_COMPA_vect)
{
    // action to be done every 10 millisec
}
