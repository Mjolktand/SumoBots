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

static volatile uint16_t timer_counter = 0;

void bot2_init();

void bot2_instructions();

#endif
