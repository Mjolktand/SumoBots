#ifndef _LINESENSOR_H_
#define _LINESENSOR_H_

void linesens_on();

void linesens_off();

void linesens_init();

void linesens_charge();

void linesens_print_values(uint8_t sensorval[]);

void linesens_read();

void linesens_10us_delay();


#endif // _LINESENSOR_H_
