//PWM test

#include<avr/io.h>
#include "mylib/PWM.h"
#include<util/delay.h>

int main()
{
	int del=50;
	PWM_INIT(1);
	while(1)
	{
		for(int i=0;i<=300;i++)
		{
			PWM_WRITE(1,'A',i);
			_delay_ms(del);
		}
		for(int i=300;i>=0;i--)
		{
			PWM_WRITE(1,'A',i);
			_delay_ms(del);
		}
		
	}

return 0;
}