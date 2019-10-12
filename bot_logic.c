#include <avr/io.h>
#include <stdio.h>

#include "bot_logic.h"
#include "linesensor.h"
#include "motors.h"
#include "motors.h"
#include "rangesensor.h"
#include "timer.h"
#include "led.h"
#include "button.h"

enum POSITION {NONE = 0, CENTER = 1, LEFT = 2, RIGHT =3 };
uint8_t line_pos;
uint8_t enemy_detected;
uint8_t standby = 0;
uint16_t big_count = 0;
volatile uint16_t timer_counter;

void bot_init()
{

	linesens_init();
	rangesensor_init();
	motors_init();
	led_init();
	button_init();
	timer1_init();
	led_1_on();
}

void bot_check_button(){
			if(button_logic_stop()){
				motor_full_stop();
				printf("BUTTON PRESS");
				standby = 1;
			}
}


void bot_rangecheck(){
	uint8_t range = rangesensor_read_cm();
	if(range > 10 && range < 40)	{
		printf("%d \n", range);
		motor_straight(MOTORS_FORWARD, 255);
		enemy_detected = 1;
	}
	else{
		enemy_detected = 0;
	}
}

void bot_wait(uint16_t timer_compare){
	big_count += timer_counter;
	timer_counter = 0;
	printf("WAIT \n");
	while(timer_counter < timer_compare){
		bot_check_button();
	}
}

void bot_wait_while_rangechecking(uint16_t timer_compare){
	big_count += timer_counter;
	timer_counter = 0;
	printf("WAIT WHILE RANGECHECKING \n");
	while(timer_counter < timer_compare && enemy_detected == 0){
			bot_check_button();
			bot_rangecheck();
	}
}

void bot_spin_scan(){
	motor_spin(MOTORS_CLOCKWISE, 255);
	printf("BOT SPIN ATTACK MODE \n");
	bot_wait_while_rangechecking(300);
	if(enemy_detected == 1){
		return;
	}
	motor_spin(MOTORS_COUNTER_CLOCKWISE, 255);
	bot_wait_while_rangechecking(300);
}

void bot_attack(){
	motor_straight(MOTORS_FORWARD, 255);
	big_count += timer_counter;
	timer_counter = 0;
	while(enemy_detected == 1 && timer_counter < 700){
		bot_rangecheck();
	}
	if(enemy_detected == 1){
		motor_turn(MOTORS_BACKWARD, 255, 100);
		bot_wait(300);
		motor_straight(MOTORS_FORWARD, 255);
	}
	bot_rangecheck();

}

void bot_instructions()
{
  while(1)
  {
		linesens_read();
		line_pos = line_bot_set_data();
		//linesens_print_values();
		if(line_pos == NONE){
			motor_straight(MOTORS_FORWARD, 255);
		}
		else if(line_pos == CENTER){
			printf("TURNING AROUND \t");
			motor_straight(MOTORS_BACKWARD, 255);
			bot_wait(200);
			motor_spin(MOTORS_CLOCKWISE, 255);
			bot_wait(700);
			motor_straight(MOTORS_FORWARD, 255);
		}
		else if(line_pos == LEFT){
			printf("ADJUSTING CLOCKWISE \t");
			motor_spin(MOTORS_CLOCKWISE, 255);
			bot_wait(200);
			motor_straight(MOTORS_FORWARD, 255);
		}
		else if(line_pos == RIGHT){
			printf("ADJUSTING COUNTER CLOCKWISE \t");
			motor_spin(MOTORS_COUNTER_CLOCKWISE, 255);
			bot_wait(200);
			motor_straight(MOTORS_FORWARD, 255);
		}
		//bot_rangecheck();
		//if(enemy_detected == 1){
			//bot_attack();
		//}
		bot_check_button();
		if(standby == 1){
			standby = 0;
			return;
		}
		if(big_count > 3000){
			big_count = 0;
			bot_spin_scan();
		}
  }

}
