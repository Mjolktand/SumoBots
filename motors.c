#include <avr/io.h>
#include <stdio.h>

#include "motors.h"

void motors_init()
{
	DDRB |= (1 << DDB4) | (1 << DDB5);

	TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1 << CS21) | (0 << CS20);
	TCCR2B &= ~(1 << CS22);

	//pin 3; PWM A OCR2A
	//pin 11; PWM B OCR2B
}

void motor_control(uint8_t motor, uint8_t direction, uint8_t speed)
{
	if (motor == MOTOR_A)
	{
		printf("Motor A\n");
		if (direction == 1)
		{
			PORTB |= (1 << DDB4);
		}
		else
		{
			PORTB &= ~(1 << DDB4);
		}

		OCR2A = speed;
	}
	else if (motor == MOTOR_B)
	{
		printf("Motor B\n");
		if (direction == 1)
		{
			PORTB |= (1 << DDB5);
		}
		else
		{
			PORTB &= ~(1 << DDB5);
		}

		OCR2B = speed;
	}
}

void motor_full_stop()
{
	OCR2A = 0;
	OCR2B = 0;
}
