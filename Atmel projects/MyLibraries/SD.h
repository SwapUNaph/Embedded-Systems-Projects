
/* library to interface sd card with atmega 8
author: Swapneel Naphade*/
#ifndef
#define SD

#define rx PINB6
#define tx PINB5
#define clk PINB7
#define cs PINB4

void SPI_init(void)
{
	DDRB |= (1<<tx)|(1<<clk)|(1<<cs);		//outputs
	DDRB &= ~(1<<rx);						//inputs
	SPCR |= (1<<SPE);                     //SPI enable
    SPCR |= (1<<MSTR);                     //Master SPI mode
    SPCR &= ~(1<<SPR1);                  //fosc/16
    SPCR |= (1<<SPR0);                    //fosc/16
    SPSR &= ~(1<<SPI2X);                //speed is not doubled
    PORTB &= ~(1<<CS);                   //Enable CS pin for the SD card
}

char SPI_sendchar(char c)
{
	char receivechar=0;
	SPDR=c;							//send c
	while(!(SPSR & (1<<SPIF)));	//wait till c is received
	receivechar=SPDR;				
	return (receivechar);			//return ack
}

char Command(char cmd, uint16_t ArgH, uint16_t ArgL, char crc ) {
    SPI_sendchar(0xFF);
    SPI_sendchar(cmd);
    SPI_sendchar((uint8_t)(ArgH >> 8));
    SPI_sendchar((uint8_t)ArgH);
    SPI_sendchar((uint8_t)(ArgL >> 8));     SPI_sendchar((uint8_t)ArgL);
    SPI_sendchar(crc);
    SPI_sendchar(0xFF);
    return SPI_sendchar(0xFF);                // Returns the last byte received
}
#end if //SD