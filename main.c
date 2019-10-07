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

void main (void)
{
	linesens_init();
	uart_init();

	while(1)
	{
		linesens_read();
		_delay_ms(1000);
	}
}
