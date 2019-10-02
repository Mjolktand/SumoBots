#ifndef _MOTORS_H_
#define _MOTORS_H

#define MOTOR_A 0
#define MOTOR_B 1

#define BACKWARD 0
#define FORWARD 1

void motors_init();

void motor_control(uint8_t motor, uint8_t direction, uint8_t speed);

void motor_full_stop();

#endif // _MOTORS_H
