#ifndef _BOT_LOGIC_H_
#define _BOT_LOGIC_H

static volatile uint16_t timer_counter = 0;
static uint16_t counter_compare = 0;
static volatile uint8_t instruction = 0;
static volatile uint8_t alert = 0;

void bot_init();

void bot_instructions();

#endif
