#include <avr/io.h>
#include <stdio.h>

#include "bot2_logic.h"
#include "linesensor.h"
#include "motors.h"
#include "motors.h"
#include "rangesensor.h"
#include "timer.h"
#include "led.h"
#include "button.h"

static enum INSTRUCTION instruction = MOVE_FORWARDS;
static uint16_t timer_compare = 0;

void bot2_init()
{
	linesens_init();
	rangesensor_init();
	motors_init();
	led_init();
	button_init();
	timer1_init();
	led_1_on();
}

void linesensor_activated()
{
	motor_straight(MOTORS_BACKWARD, 200);
	timer_compare = 100;
	timer_counter2 = 0;
	instruction = MOVE_SPIN;
}

void rangesensor_activated()
{
	move_forwards();
}

void move_spin()
{
	if(timer_counter2 >= timer_compare)
	{
		motor_spin(MOTORS_CLOCKWISE, 250);
		timer_compare = 150;
		timer_counter2 = 0;
		instruction = MOVE_FORWARDS;
	}
}

void move_forwards()
{
	if(timer_counter2 >= timer_compare)
	{
		motor_straight(MOTORS_FORWARD, 255);
		timer_compare = 200;
		timer_counter2 = 0;
		instruction = MOVE_SPIN;
	}
}

void bot2_instructions()
{
	uint8_t range = 0;

	while (1)
	{
		linesens_read();
		if (linesens_check_results())
		{
			instruction = LINESENSOR_ACTIVATED;
		}
		else
		{
			range = rangesensor_read();
			if (range > 30 && range < 130)
			{
				instruction = RANGESENSOR_ACTIVATED;
				range = 0;
			}
		}

		switch (instruction)
		{
			case LINESENSOR_ACTIVATED:
				linesensor_activated();
				break;

			case RANGESENSOR_ACTIVATED:
				rangesensor_activated();
				break;

			case MOVE_SPIN:
				move_spin();
				break;

			case MOVE_FORWARDS:
				move_forwards();
				break;

			default:
				move_forwards();
				break;
		}

		if (button_logic_stop())
		{
			motor_full_stop();
			return;
		}
	}
}
