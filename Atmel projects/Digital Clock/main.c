
//Digital Clock

//AUTHOR: SWAPNEEL NAPHADE
//23/5/2015


//D4-->PB0	//FOR LCD
//D5-->PB1
//D6-->PB2
//D7-->PB3
//EN-->PD0
//RS-->PD1
//R/W-->GND
//GND--BUTTON1--PD3
//GND--BUTTON2--PD4


#include<avr/io.h>
#include<string.h>
#include<mylib/LCD.h>
#include<util/delay.h>
#define MINUTE_PIN PORTD4
#define HOUR_PIN PORTD3
int count=0;
uint8_t hour=0,minute=0,second=0;
void TIME(void);
void HOUR(void);
void MINUTE(void);
void SET_TIME(void);
int main(void)
{
	LCD_INIT();
	PORTD |= (1<<HOUR_PIN|1<<MINUTE_PIN);//PULL UP RESISTOR
	
	while(1)
	{
		HOUR();
		MINUTE();
		TIME();
	}
		
}

void TIME()
{
	_delay_ms(100);
	count++;
	if(count>10)
	{
		second++;
		count=0;
	}
	if(second>59)
	{
		second=0;
		minute++;
	}
	if(minute>59)
	{
		hour++;
		minute=0;
	}
	
	if(hour>24)
		hour=0;
	LCD_CLEAR();
	_delay_ms(1);
	LCD_WRITE("Swapneel's Clock");
	LCD_SETCURSOR(4,1);
	LCD_WRITE_NUM(hour,3);
	LCD_WRITE(":");
	LCD_WRITE_NUM(minute,3);
	LCD_WRITE(":");
	LCD_WRITE_NUM(second,3);
}	
void HOUR()
{
	if(!(PIND & (1<<HOUR_PIN)))
	{
		_delay_ms(200);
		hour++;
		if(hour>24) hour=1;
	}

}

void MINUTE()
{
	if(!(PIND & (1<<MINUTE_PIN)))
	{
		_delay_ms(200);
		minute++;
		if(minute>60) minute=0;
	}
	
}




