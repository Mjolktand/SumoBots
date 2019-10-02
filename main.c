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
	printf("Motor init\n");
	motors_init();
	_delay_ms(5000);
	printf("Motor START\n");
	motor_control(MOTOR_A, FORWARD, 100);
	motor_control(MOTOR_B, FORWARD, 100);
	_delay_ms(2000);
	motor_control(MOTOR_A, FORWARD, 255);
	motor_control(MOTOR_B, FORWARD, 255);
	_delay_ms(2000);
	motor_full_stop();
	motor_control(MOTOR_A, FORWARD, 50);
	motor_control(MOTOR_B, BACKWARD, 50);
	_delay_ms(3000);
	motor_control(MOTOR_A, FORWARD, 255);
	motor_control(MOTOR_B, FORWARD, 255);
	_delay_ms(2000);
	motor_full_stop();
	printf("Motor STOP\n");
}
