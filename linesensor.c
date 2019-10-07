#include <avr/io.h>

#include "linesensor.h"
#include <stdio.h>

//sensor pins: 4, 5, 6, 7, 8, 9
//LEDon pin: 10/PB2



void linesens_init()
{
  DDRB |= (1 << DDB2);
  linesens_on();
}

void linesens_on(){
  PORTB |= (1 << PORTB2);
}

void linesens_off(){
  PORTB &= ~(1 << PORTB2);
}
void linesens_10us_delay(){
//set CTC mode
  TCCR0A |= (1 << WGM01);
  OCR0A = 19;
//set prescaler to 8
  TCCR0B |= (1 << CS01);
  while (!(TIFR0 & (1 << OCF0A))){
    ; 	}

//set prescaler to 0, timer stopped
  TCCR0B &= ~(1 << CS01);
  //reset check flag
  TIFR0 |= (1 << OCF0A);
}

void linesens_charge(){
  DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
  DDRB |= (1 << DDB0) | (1 << DDB1);

  PORTD |= (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
  PORTB |= (1 << PORTB0) | (1 << PORTB1);

  linesens_10us_delay();

  PORTD &= ~((1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7));
  PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
}


void linesens_read(){
  //memset(sensorValues, 0, 6); //sets all sensorvalues to 0
  uint8_t sensorValues[] = {0, 0, 0, 0, 0, 0};
  TCCR0A |= (1 << WGM01);
  OCR0A = 155;


  linesens_charge();

  DDRD &= ~((1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7));
  DDRB &= ~((1 << DDB0) | (1 << DDB1)); //sets pins to inputs


  TCCR0B |= (1 << CS02); //starts 2500us timer

  while (!(TIFR0 & (1 << OCF0A))){
    if (!(PINB & (1 << PINB1)) && sensorValues[0] == 0){
        sensorValues[0] = TCNT0;
      }
     if (!(PINB & (1 << PINB0)) && sensorValues[1] == 0){
         sensorValues[1] = TCNT0;
       }
     if (!(PIND & (1 << PIND7)) && sensorValues[2] == 0){
         sensorValues[2] = TCNT0;
       }
     if (!(PIND & (1 << PIND6)) && sensorValues[3] == 0){
         sensorValues[3] = TCNT0;
       }
     if (!(PIND & (1 << PIND5)) && sensorValues[4] == 0){
         sensorValues[4] = TCNT0;
       }
     if (!(PIND & (1 << PIND4)) && sensorValues[5] == 0){
         sensorValues[5] = TCNT0;
       }
  }
  TCCR0B &= ~(1 << CS02);
  TIFR0 |= (1 << OCF0A);
  linesens_print_values(sensorValues);
}

void linesens_print_values(uint8_t sensorval[]){
  for(uint8_t i = 0; i < 6; i++){
    printf("%d", sensorval[i]);
    printf("\t");
  }
  printf("\n");

}
