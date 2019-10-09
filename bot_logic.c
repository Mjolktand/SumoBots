#include <avr/io.h>
#include <stdio.h>

#include "linesensor.h"
#include "motors.h"
#include "bot_logic.h"
#include "motors.h"
#include "rangesensor.h"
#include "timer.h"
#include "led.h"
#include "button.h"

void bot_init()
{
	linesens_init();
	rangesensor_init();
	motors_init();
	led_init();
	button_init();
	timer1_init();
}

void bot_instructions()
{
  while(1)
  {
    switch(instruction)
    {
      case 1:
        motor_full_stop();
        instruction = 2;
        counter_compare = 0;
        break;

      case 2:
        if(timer_counter >= counter_compare)
        {
          motor_straight(MOTORS_BACKWARD, 255);
          instruction = 3;
          counter_compare = 100;
          timer_counter = 0;
        }
        break;

      case 3:
        if(timer_counter >= counter_compare)
        {
          motor_spin(MOTORS_CLOCKWISE, 155);
          instruction = 0;
          counter_compare = 100;
          timer_counter = 0;
        }
        break;

      default:
        if(timer_counter >= counter_compare)
        {
          motor_straight(MOTORS_FORWARD, 150);

        }
    }
  }
}
