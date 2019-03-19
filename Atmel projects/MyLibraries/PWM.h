/********************
PWM Library
Author:Swapneel Naphade

User Manual
PWM_INIT(OCR_NUM);--->Initialize PWM at pwm port.
PWM_WRiTE(OCR_NUM,OCR_A/B,PWM_VALUE);--->Write PWM value to pin specified by ocr number

*******************/
#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED
#include<avr/io.h>

void PWM_INIT(int);
void PWM_WRITE(int, char, int);

void PWM_INIT(int c)
{
	switch (c)
	{
	case 0:DDR = 0b01100000;
			TCCR0A |= 1<<WGM01|1<<COM0A1;//Fast PWM, Inverted mode
			TCCR0B |= 1<<WGM02|1<<WGM03|1<<CS00;//Fast PWM, No prescaler
			ICR0=19999;
			break;
	
	case 1:DDRB = 0b00000110;
			TCCR1A |= 1<<WGM11|1<<COM1A1;//Fast PWM, Inverted mode
			TCCR1B |= 1<<WGM12|1<<WGM13|1<<CS10;//Fast PWM, No prescaler
			ICR1=19999;
			break;
	case 2:DDRB |= 1<<PINB3;
			DDRD |= 1<<PINB3;
			TCCR2A |= 1<<WGM21|1<<COM2A1;//Fast PWM, Inverted mode
			TCCR2B |= 1<<WGM22|1<<WGM23|1<<CS20;//Fast PWM, No prescaler
			ICR2=19999;
			break;
	default:DDRB = 0b00000110;
			TCCR1A |= 1<<WGM11|1<<COM1A1;//Fast PWM, Inverted mode
			TCCR1B |= 1<<WGM12|1<<WGM13|1<<CS10;//Fast PWM, No prescaler
			ICR1=19999;
			break;
	}
}

void PWM_WRITE(int ocr_num,char ocr, int pwm_val)
{
	if(ocr=='a'||ocr=='A')
	{
		if(ocr_num==1)OCR1A=pwm_val;
		else if(ocr_num==2) OCR2A=pwm_val;
		else OCR0A=pwm_val;
	}
	else if(ocr=='b'||ocr=='B')
	{
		if(ocr_num==1)OCR1B=pwm_val;
		else if(ocr_num==2) OCR2B=pwm_val;
		else OCR0B=pwm_val;
	}
}

#endif//PWM.h