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

void bot2_instructions()
{
	static enum INSTRUCTION instruction = 0;
	static uint16_t timer_compare = 0;
	uint8_t cm = 0;

	while (1)
	{
		linesens_read();
		if (linesens_check_results())
		{
			instruction = LINESENSOR_ACTIVATED;
		}
		else if (cm = rangesensor_read_cm() > 0 && cm < 40)
		{
			instruction = RANGESENSOR_ACTIVATED;
		}

		switch (instruction)
		{
			case LINESENSOR_ACTIVATED:
				motor_straight(MOTORS_BACKWARD, 255);
				timer_compare = 100;
				timer_counter = 0;
				instruction = MOVE_SPIN;
				break;

			case MOVE_SPIN:
				if(timer_counter >= timer_compare)
				{
					motor_spin(MOTORS_CLOCKWISE, 150);
					timer_compare = 100;
					timer_counter = 0;
					instruction = MOVE_FORWARDS;
				}
				break;

			case MOVE_FORWARDS:
				if(timer_counter >= timer_compare)
				{
					motor_straight(MOTORS_FORWARD, 255);
					timer_compare = 200;
					timer_counter = 0;
					instruction = MOVE_SPIN;
				}
				break;

			default:
				motor_straight(MOTORS_FORWARD, 255);
				break;
		}

		if (button_logic_stop())
		{
			motor_full_stop();
			return;
		}
	}
}
