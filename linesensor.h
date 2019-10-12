#ifndef _LINESENSOR_H_
#define _LINESENSOR_H_

volatile uint8_t sensorValues[6];

void linesens_on();

void linesens_off();

void linesens_init();

void linesens_charge();

void linesens_print_values();

void linesens_read();

void linesens_10us_delay();

uint8_t linesens_check_results();


#endif // _LINESENSOR_H_
