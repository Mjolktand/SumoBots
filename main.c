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
	rangesensor_init();
	uart_init();
	uint8_t cm = 0;

	while(1)
	{
		cm = rangesensor_read_cm();
		printf("%d\n", cm);
		_delay_ms(1000);
	}
}
