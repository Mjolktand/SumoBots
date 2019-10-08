#include <avr/io.h>
#include <stdio.h>

#include "linesensor.h"
#include "motors.h"
#include "bot_logic.h"


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
