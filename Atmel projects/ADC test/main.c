//ADC to change delay of blinking LED
#include <avr/io.h>
#include "mylib/ADC.h"
#include "mylib/LCD.h"
#include <util/delay.h>



int main(void)
{
	uint16_t adcval;
	LCD_INIT();
	ADC_INIT();
	LCD_SETCURSOR(1,1);
	LCD_WRITE_STRING("Swapneel");
	while(1)
	{
		LCD_SETCURSOR(1,1);
		adcval=ADC_READ(5);
		LCD_WRITE_NUM((int) adcval,4);
		LCD_WRITE_STRING("  ");
		_delay_ms(100);
	}
return 0;

}