//Weather station
//author: Swapneel Naphade


#include<avr/io.h>
#include "mylib/ADC.h"
#include "mylib/LCD.h"
#include<util/delay.h>

int read_temp(uint8_t temp)
{
	int t;
	t=ADC_READ(temp);
	return t;
}

int read_light(uint8_t light)
{
	
	int l;
	l=ADC_READ(light);
	return l;
}


int main()
{
	int temp=0;
	int light=0;
	ADC_INIT();
	LCD_INIT();
	LCD_SETCURSOR(3,1);
	LCD_WRITE_STRING("Welcome to");
	_delay_ms(1000);
	LCD_CLEAR();
	LCD_SETCURSOR(10,1);
	LCD_WRITE_STRING("Swapneel's weather station!");
	LCD_SCROLL_LEFT(15,500);
	LCD_CLEAR();
	while(1)
	{
		temp=read_temp(5);
		light=read_light(4);
		LCD_CLEAR();
		LCD_SETCURSOR(1,1);
		LCD_WRITE_STRING("Temperature:");
		LCD_WRITE_NUM(temp,4);
		LCD_SETCURSOR(1,2);
		LCD_WRITE_STRING("Light:");
		LCD_WRITE_NUM(light,4);
		_delay_ms(1000);
	}

return 0;
}

