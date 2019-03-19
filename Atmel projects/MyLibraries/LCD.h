//An LCD library for interfacing Atmega 8 to a 16X2 LCD...
//Author:SWAPNEEL NAPHADE

//This code is for 4 bit mode. To use 8 bit mode some changes are must.
//To use 8 bit mode set command in LCD_INIT and make higher/lower bits to full byte in LCD_CMD and LCD_DATA


//Interface manual:
//Enable -->           PORTD PIN0
//Register Select -->  PORTD PIN1
//Read/Write -->       PORTD PIN2
//D0 --> PORTB PIN0 |
//D1 --> PORTB PIN1 |
//D2 --> PORTB PIN2 |
//D3 --> PORTB PIN3 | for 8 bit data (for 4 bit mode PINB 0,1,2,3 to LCD pin D4,D5,D6,D7)
//D4 --> PORTB PIN4 |
//D5 --> PORTB PIN5 |
//D6 --> PORTB PIN6 |
//D7 --> PORTB PIN7 |
//Commands :
//LCD_INIT(); --> Initializes the LCD for Display PS:Cursor OFF
//LCD_WRITE("string"); --> To display characters
//LCD_WRITE_NUM(value,width); -->To display number of specified width
//LCD_SETCURSOR(x,y); -->To set cursor coordinates(1st digit is x=1, y=1)
//LCD_CLEAR(); -->Erases LCD memory 
//LCD_SCROLL_LEFT(amount,step_delay_ms);-->To scroll the diplay left by 'amount' position with 'step_delay_ms' time delay
//LCD_SCROLL_RIGHT(amount,step_delay_ms);-->To scroll the diplay right by 'amount' position with 'step_delay_ms' time delay
//LCD_CURSOR_LEFT();-->To move cursor left by one digit
//LCD_CURSOR_RIGHT();-->To move cursor right by one digit
//LCD_DISPLAY_CONTROL(ON/OFF);-->To ON/OFF display
//LCD_CURSOR_CONTROL(ON/OFF/BLINK);-->To ON/OFF/BLINK cursor
//LCD_CLEAR_LINE(line);-->To clear the line and start at the first digit on line.



#ifndef LCD
#define LCD

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define DATADIR_PORTB DDRB
#define DATADIR_PORTD DDRD
#define LCD_CONTROL PORTD
#define LCD_DT PORTB
#define EN PORTD0
#define RS PORTD1
#define RW PORTD2

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_WRITE_STRING(char *);
void LCD_WRITE_CHAR(char);
void LCD_WRITE_NUM(unsigned char, unsigned char);
void LCD_SETCURSOR(uint8_t, uint8_t);
void LCD_CLEAR(void);
void LCD_FLASH(void);
void LCD_SHIFT_DISPLAY_LEFT(void);
void LCD_SHIFT_DISPLAY_RIGHT(void);
void LCD_SCROLL_LEFT(uint8_t,unsigned int);
void LCD_SCROLL_RIGHT(uint8_t,unsigned int);
void LCD_CURSOR_LEFT(void);
void LCD_CURSOR_RIGHT(void);
void LCD_DISPLAY_CONTROL(uint8_t);
void LCD_CURSOR_CONTROL(uint8_t);
void LCD_CLEAR_LINE(uint8_t);

unsigned char InitColumn[2]={0,64};

void LCD_INIT()
{
	_delay_ms(2);
	DATADIR_PORTD |= (1<<EN|1<<RS|1<<RW);//Enable, RS, RW OUTPUT
	DATADIR_PORTB = 0xFF;//PORTB output
	_delay_ms(20);
	LCD_CMD(0x30);//Initialisation of LCD
	LCD_CMD(0x30);//       "         "
	LCD_CMD(0X20);//       "         "
	LCD_CMD(0x01);//Clear Screen
	_delay_ms(2);
	LCD_CMD(0x28);//4-bit mode
	//LCD_CMD(0x038);//8-bit mode
	_delay_us(50);
	LCD_CMD(0x0C);//Display ON cursor OFF
	_delay_us(50);
	//LCD_CMD(0x06);//Cursor Auto-increment
	_delay_us(50);
	LCD_CMD(0x80);//Set cursor to 1st position on display
}

void LCD_CMD(unsigned char cmd)//Give command to LCD
{
	_delay_us(100);
	LCD_CONTROL &=~((1<<RW)|(1<<RS));//Write mode and Command mode
	LCD_DT = 0x00;//Clear PORTB
	LCD_DT = ((cmd>>4) & 0x0F);//Higher bits of command on PORTB
	LCD_FLASH();//LCD listens
	LCD_DT = 0x00;//Clear PORTB
	LCD_DT = (cmd & 0x0F);//Lower bits of command on PORTB
	LCD_FLASH();//LCD listens
	LCD_DT = 0;//PORTB set to 0
}

void LCD_DATA(unsigned char data)//Load data to LCD
{
	_delay_us(100);
	LCD_CONTROL &=~(1<<RW);//Write mode
	LCD_CONTROL |=1<<RS;//Output mode
	LCD_DT = 0x00;//Clear PORTB
	LCD_DT = ((data>>4) & 0x0F);//Higher bits of command on PORTB
	LCD_FLASH();//LCD listens
	LCD_DT = 0x00;//Clear PORTB
	LCD_DT = (data & 0x0F);//Lower bits of command on PORTB
	LCD_FLASH();//LCD listens
	LCD_DT = 0;//PORTB set to 0
}

void LCD_WRITE_CHAR(char C)
{
	LCD_DATA(C);
	_delay_us(100);
}

void LCD_WRITE_STRING(char *string)
{
	while(*string>0)
	{
		LCD_DATA(*string++);
		_delay_us(100);
	}
}

void LCD_WRITE_NUM(unsigned char val, unsigned char width)
{
	unsigned char array[width];
	itoa(val,array,10);
	LCD_WRITE_STRING(array);
	_delay_us(100);
}

void LCD_SETCURSOR(uint8_t x, uint8_t y)
{
	LCD_CMD(0x80 + InitColumn[y-1] + x-1);
	_delay_ms(1);
}

void LCD_CLEAR()
{
	LCD_CMD(0x01);//Clear screen
	_delay_us(100);
}

void LCD_FLASH()
{
	LCD_CONTROL |=1<<EN;//Enable ON, LCD processing
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");//Some delay
	LCD_CONTROL &=~(1<<EN);//Enable OFF, LCD processing
}
void LCD_SHIFT_DISPLAY_LEFT()
{
    LCD_CMD(0x18);//Shift display left
    _delay_us(100);
}

void LCD_SHIFT_DISPLAY_RIGHT()
{
    LCD_CMD(0x1C);//Shift display right
    _delay_us(100);
}

void LCD_SCROLL_LEFT(uint8_t scrollamount,unsigned int scrolldelayms)
{
    for(int i=0;i<scrollamount; i++ )
    {
        LCD_SHIFT_DISPLAY_LEFT();
        _delay_ms(scrolldelayms);
    }
	_delay_us(100);
}

void LCD_SCROLL_RIGHT(uint8_t scrollamount,unsigned int scrolldelayms)
{
    for(int i=0; i<scrollamount; i++ )
    {
        LCD_SHIFT_DISPLAY_RIGHT();
        _delay_ms(scrolldelayms);
    }
	_delay_us(100);
}

void LCD_CURSOR_LEFT(void)
{
	LCD_CMD(0x10);//Move cursor left by one digit
	_delay_us(100);
}
void LCD_CURSOR_RIGHT(void)
{
	LCD_CMD(0x14);//Move cursor right by one digit
	_delay_us(100);
}

#define ON 1
#define OFF 0
#define BLINK 2
void LCD_DISPLAY_CONTROL(uint8_t command)
{
	switch(command)
	{
		case 1: LCD_CMD(0x0C);break;//Display ON
		case 0: LCD_CMD(0x08);break;//Display OFF
	}
	_delay_us(100);
}

void LCD_CURSOR_CONTROL(uint8_t command)
{
	switch(command)
	{
		case 0: LCD_CMD(0x0C);break; //Cursor OFF
		case 1: LCD_CMD(0x0E);break;//Cursor ON
		case 2: LCD_CMD(0x0F);break;//Cursor blinking
	}
	_delay_us(100);
}

void LCD_CLEAR_LINE(uint8_t line)
{
	LCD_SETCURSOR(1,line);
	LCD_WRITE_STRING("                ");
	LCD_SETCURSOR(1,line);

}
#endif //LCD
