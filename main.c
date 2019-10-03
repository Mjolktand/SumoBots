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

void main (void)
{
	motors_init();
	_delay_ms(5000);
	motor_straight(MOTORS_BACKWARD, 100);
	_delay_ms(2000);
	motor_straight(MOTORS_FORWARD, 255);
	_delay_ms(3000);
	motor_turn(MOTORS_BACKWARD, 100, 200);
	_delay_ms(2000);
	motor_full_stop();
	_delay_ms(2000);
	motor_spin(MOTORS_CLOCKWISE, 100);
	_delay_ms(2000);
	motor_spin(MOTORS_COUNTER_CLOCKWISE, 255);
	_delay_ms(3000);
	motor_full_stop();
}
