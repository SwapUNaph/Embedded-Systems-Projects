//LCD test
#include<avr/io.h>
#include "mylib/LCD.h"
#include<util/delay.h>
char c[6];
int main(void)
{
	LCD_INIT();
	LCD_SETCURSOR(6,1);

	LCD_WRITE_STRING("SWAPNEEL");
	while(1)
	{
			LCD_SCROLL_LEFT(1,200);
	}
	return 0;
}