/*Swapneel Naphade
Dynamometer*/
//FCPU= 16Mhz
//The timer counts for each rotation are sent via uasrt
//Programme gives error message when rotation is less than 60rpm

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#include<mylib/USART.h>

#define check_led PINB1
#define error_led PINB2

//void uart_send(void);
void timer1_init(void);

volatile int rot_time=0;


int main(void)
{
	DDRD = 1<<PD2;		// Set PD2 as input (Using for interupt INT0) connected to a hall effect sensor
	PORTD = 1<<PD2;
	DDRB = (1<<check_led)|(1<<error_led);//setting up indicating leds
	USART_INIT(9600,0,8,EVEN);
	//enable interupts
	sei();
	GICR |= 1<<INT0;//Enable interrupt 0
	MCUCR |= 1<<ISC01;//falling edge sensing
	timer1_init();
	
	while(1)
	{
		if(TCNT1>12000)
			PORTB |= (1<<error_led);
		else PORTB &= ~(1<<error_led);
		PORTB &= ~(1<<check_led);
	}
	return 0;
	
}

void timer1_init(void)
{
    // set up timer with 1024 prescaling
    TCCR1B |= (1 << CS12)|(1 << CS10);
    // initialize counter
    TCNT1 = 0;
}

//interrupt code for sensing falling edge 
ISR(INT0_vect) 
{
	//int0
	if(TCNT1 < 12000 )
	{
		rot_time=TCNT1;
		TCNT1=0;
		USART_TRANSMIT_NUM(rot_time);
		PORTB &= ~(1<<error_led);
		PORTB |= 1<<check_led;
	}
	else
	{
		TCNT1=0;
		PORTB |= 1<<error_led;
	}
}

/*
void uart_send(void)
{
	PORTB |= (1<<check_led);
	USART_TRANSMIT_NUM(uart_buffer[0]);
	char num_buffer[6]={"00000"};
	itoa(uart_buffer[0],num_buffer,10);
	 for(int j=0;num_buffer[j]!='\0';)
		USART_TRANSMIT(num_buffer[j++]);
	 

	for(int j=0;uart_buffer[j]!='\0';j++)
		uart_buffer[j]=uart_buffer[j+1];
	i--;
}
*/