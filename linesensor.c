#include <avr/io.h>
#include <stdio.h>

#include "linesensor.h"
#include "timer.h"



//sensor pins: 4, 5, 6, 7, 8, 9
//LEDon pin: 10

void linesens_init()
{
  DDRB |= (1 << DDB2);
}

void linesens_on()
{
  PORTB |= (1 << PORTB2);
}

void linesens_off(){
  PORTB &= ~(1 << PORTB2);
}

void linesens_charge()
{
  DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
  DDRB |= (1 << DDB0) | (1 << DDB1);

  PORTD |= (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
  PORTB |= (1 << PORTB0) | (1 << PORTB1);

  timer0_delay_10us();

  PORTD &= ~((1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7));
  PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
}

void linesens_read()
{
  linesens_on();

  for(uint8_t i = 0; i < 6; i++){
      sensorValues[i] = 0;
    }

  linesens_charge();

  TCCR0A |= (1 << WGM01);
  OCR0A = 155;
  TCCR0B |= (1 << CS02); //starts 2500us timer (16 us per tick)

  DDRD &= ~((1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7));
  DDRB &= ~((1 << DDB0) | (1 << DDB1)); //sets pins to inputs

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

  timer0_stop();
  linesens_off();
}

uint8_t linesens_check_results()
{
  for(uint8_t i; i < 6; i++)
  {
    if(sensorValues[i] != 0)
    {
      return 1;
    }
  }
  return 0;
}

void linesens_print_values()
{
  for(uint8_t i = 0; i < 6; i++){
    printf("%d", sensorValues[i]);
    printf("\t");
  }
  printf("\n");
}
