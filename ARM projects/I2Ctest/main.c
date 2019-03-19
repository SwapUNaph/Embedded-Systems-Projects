#include "stm32f10x_usart.h"
#include "MPU6050.h"
#include "stdio.h"
#include "string.h"

#define I2C_SLAVE_ADD 0x68

void writeArrayToString(char *datastr, int16_t *array);
void USART_send(char *buffer);
void USART_config(uint32_t baudrate);
void wait(unsigned long cycles);
/********************* main() **************************/
int main(void)
{
	USART_config(115200);
	MPU6050_I2C_Init();
	MPU6050_Initialize();
	int16_t AccelGyro[6];
	char data[64];
    while(1)
    {
		 MPU6050_GetRawAccelGyro(AccelGyro);
		 writeArrayToString(data,AccelGyro);
		 USART_send(data);
		 wait(4000000);
    }
}

/*******************************************************/
void writeArrayToString(char *datastr, int16_t *array){
	sprintf(datastr,"%d,%d,%d,%d,%d,%d\n", array[0],array[1],array[2],array[3],array[4],array[5]);
}

void USART_config(uint32_t baudrate){
	//ENABE CLOCK FOR PINA9, PINA10 AND USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitTypeDef gpio;
	//INITIALIZE GPIOA PIN 9 TO ALTERNATE FUNCTION
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio);

	//INITIALIZE GPIOA PIN 10 TO FLOATING INPUT
	gpio.GPIO_Pin = GPIO_Pin_10;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	//CONFIGURE USART1
	USART_InitTypeDef usart;
	USART_StructInit(&usart);
	usart.USART_BaudRate = baudrate;	//BAUDRATE 115200
	usart.USART_WordLength = USART_WordLength_8b;	//8BIT WORD LENGTH
	usart.USART_StopBits = USART_StopBits_1;	//1 STOPBIT
	usart.USART_Parity = USART_Parity_No;	//NO PARITY CHECK
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //NO HARDWARE FLOW CONTROL
	usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //RX/TX ENABLE
	USART_Init(USART1, &usart);	//INITIALIZE USART1
	USART_Cmd(USART1, ENABLE);	//ENABLE USART1
}

void USART_send(char *buffer){
	while(*buffer)// Loop while there are more characters to send.
	{
		USART_SendData(USART1, *buffer++);//
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //wait for next character to send
	}
}

void wait(unsigned long cycles){
	while(cycles--){}
}
