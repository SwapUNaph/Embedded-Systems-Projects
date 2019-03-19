//UART test- Tansmiter ATmega 328p
#include <avr/io.h>
#include <mylib/USART.h>
#include<util/delay.h>
//PORTB1=RED BUTTON
//PORTB2=GREEN BUTTON
//PORTB3=BLUE BUTTON
int main( void )
{
USART_INIT();
PORTB = 0xFF;//PULL UP RESISITORS    
	while(1)
	{
		if(!(PINB & (1<<PINB1)))
		{
			_delay_ms(50);
			USART_TRANSMIT('r');
		}
		else if(!(PINB & (1<<PINB2)))
		{
			_delay_ms(50);
			USART_TRANSMIT('g');
		}
		else if(!(PINB & (1<<PINB3)))
		{
			_delay_ms(50);
			USART_TRANSMIT('b');
		}
	}
return 0;
}
