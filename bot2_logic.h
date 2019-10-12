#ifndef _BOT2_LOGIC_H_
#define _BOT2_LOGIC_H

enum INSTRUCTION
{
	LINESENSOR_ACTIVATED,
	RANGESENSOR_ACTIVATED,
	MOVE_FORWARDS,
	MOVE_BACKWARDS,
	MOVE_SPIN
};

volatile uint16_t timer_counter2;

void bot2_init();

void linesensor_activated();

void rangesensor_activated();

void move_spin();

void move_forwards();

void bot2_instructions();

#endif
