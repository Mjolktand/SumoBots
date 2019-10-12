#ifndef _BOT_LOGIC_H_
#define _BOT_LOGIC_H

volatile uint16_t timer_counter;

void bot_init();

void bot_wait();

void bot_wait_while_rangechecking();

void bot_attack();

void bot_check_button();

void bot_spin_scan();

void bot_rangecheck();

void bot_instructions();

#endif
