#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include <avr/io.h>
/***********
CPU clock Prescale ADC frequency ADCSRA bits set
1MHz      4           250 kHz         ADPS1
          8       125kHz           ADPS1 and ADPS0
          16       62.5 kHz         ADPS2
           32       31.25 kHz     ADPS2 and ADPS0
8 MHz     16       250 kHz         ADPS2
          32         125 kHz      ADPS2 and ADPS0
          64        62.5 kHz      ADPS2 and ADPS1 
         128       31.25 kHz     ADPS2 and ADPS1 and ADPS0
12 MHz    64        187.5 kHz     ADPS2 and ADPS1
          128       93.75 kHz      ADPS2 and ADPS1 and ADPS0
16 MHz     64       250 kHz     ADPS2 and ADPS1
          128      125 kHz      ADPS2 and ADPS1 and ADPS0
*************/

void ADC_INIT(void);
uint16_t ADC_READ(uint8_t);

void ADC_INIT()
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t ADC_READ(uint8_t ch)
{
  // select the corresponding channel 0~7
  // ANDing with ’7' will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
 
  // start single convertion
  // write ’1' to ADSC
  ADCSRA |= (1<<ADSC);
 
  // wait for conversion to complete
  // ADSC becomes ’0' again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));
 
  return (ADC);
}

#endif // ADC_H_INCLUDED
