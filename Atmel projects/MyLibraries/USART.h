//USART functions by Swapneel Naphade
//On 8/5/2015
#ifndef USART
#define USART

#include<avr/io.h>
#include<stdlib.h>

#define F_CPU 16000000// Clock Speed
#define EVEN 0
#define ODD 1

void USART_INIT(unsigned int, int, int, int);
void USART_TRANSMIT( unsigned char );
unsigned char USART_RECIEVE( void );
void USART_TRANSMIT_NUM( int );

void USART_INIT(unsigned int baud, int AsyncDoubleSpeed,int DataSize,int Parity)
{
	uint16_t ubrr=F_CPU/baud/16-1;
	//Put the upper part of the baud number here (bits 8 to 11)
	UBRRH = (unsigned char) (ubrr >> 8);
	//UBBRH0 = (unsigned char) (ubrr >> 8);

	//Put the remaining part of the baud number here
	UBRRL = (unsigned char) ubrr;
	//UBBRL0 = (unsigned char) ubrr;

	if(AsyncDoubleSpeed == 1)UCSRA = (1 << U2X); //setting the U2X bit to 1 for double speed asynchronous

	//Enable the receiver and transmitter
	UCSRB = (1 << RXEN) | (1 << TXEN);
	//UCSRB0 = (1 << RXEN0) | (1 << TXEN0);

	//Set data bit length
	switch(DataSize)
	{
		case 6:UCSRC |= (1 << UCSZ0); //6-bit data length
				//UCSRC0 |= (1 << UCSZ00);
	           break;

		case 7:UCSRC |= (2 << UCSZ0); //7-bit data length
				//UCSRC0 |= (2 << UCSZ00);
				break;

		case 8:UCSRC |= (3 << UCSZ0); //8-bit data length
				//UCSRC0 |= (3 << UCSZ00);
				break;

		case 9:UCSRC |= (7 << UCSZ0); //9-bit data length
				//UCSRC0 |= (7 << UCSZ00);
				break;
		default:break;
	}
	//Set 2 stop bits
	UCSRC = (1<<URSEL)|(1<<USBS);
	//UCSRC0 = (1<<URSEL0)|(1<<USBS0);
	switch(Parity)
	{
		case EVEN:UCSRC |= (1 << UPM1); //Sets parity to EVEN
					//UCSRC0 |= (1 << UPM01);
					break;
		case ODD:UCSRC |= (3 << UPM0); //Sets parity to ODD
					//UCSRC0 |= (3 << UPM00);
					break;
	}
}

void USART_TRANSMIT( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) );
/* Put data into buffer, sends the data */
UDR = data;
}


unsigned char USART_RECIEVE( void )
{
/* Wait for data to be received */
while ( !(UCSRA & (1<<RXC)) );
/* Get and return received data from buffer */
return UDR;
}

void USART_TRANSMIT_NUM(int data)
{
	char num_str[9];
	itoa(data,num_str,10);
	for(int i=0; num_str[i]!='\0';)
		USART_TRANSMIT(num_str[i++]);
	
}

#endif
