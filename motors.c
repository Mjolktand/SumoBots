#include <avr/io.h>
#include <stdio.h>

#include "motors.h"

void motors_init()
{
	DDRD |= (1 << DDD3);
	DDRB |= (1 << DDB3) | (1 << DDB4) | (1 << DDB5);

	TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM22) | (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1 << CS21) | (1 << CS20);
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
			PORTB |= (1 << PORTB4);
		}
		else
		{
			PORTB &= ~(1 << PORTB4);
		}

		OCR2A = speed;
	}
	else if (motor == MOTOR_B)
	{
		printf("Motor B\n");
		if (direction == 1)
		{
			PORTB |= (1 << PORTB5);
		}
		else
		{
			PORTB &= ~(1 << PORTB5);
		}

		OCR2B = speed;
	}
}

void motor_forward(uint8_t speed)
{

}

void motor_backwards(uint8_t speed)
{

}

void motor_turn(uint8_t speed_A, uint8_t speed_B)
{

}

void motor_spin(uint8_t direction, uint8_t speed)
{

}

void motor_full_stop()
{
	OCR2A = 0;
	OCR2B = 0;
}
