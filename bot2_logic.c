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
}

void bot2_instructions()
{
}
