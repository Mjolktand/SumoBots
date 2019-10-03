#ifndef _MOTORS_H_
#define _MOTORS_H

#define MOTORS_BACKWARD 0
#define MOTORS_FORWARD 1
#define MOTORS_CLOCKWISE 0
#define MOTORS_COUNTER_CLOCKWISE 1

#define MOTOR_A 0
#define MOTOR_B 1

void motors_init();

void motor_single_control(uint8_t motor, uint8_t direction, uint8_t speed);

void motor_straight(uint8_t direction, uint8_t speed);

void motor_turn(uint8_t direction, uint8_t speed_A, uint8_t speed_B);

void motor_spin(uint8_t direction, uint8_t speed);

void motor_full_stop();

#endif // _MOTORS_H
