/**
  ******************************************************************************
  * @file    main.c
  * @author  Swapneel Naphade
  * @version V1.0.0
  * @date    10-DEC-2017
  * @brief   This file contains telemetry functions definition firmware
  * of BluetoothTelemetry project.
  ******************************************************************************
  *	Copyright (c) 2017, Swapneel Naphade.
  *	All rights reserved.
  *
  *	Redistribution and use in source and binary forms are permitted
  *	provided that the above copyright notice and this paragraph are
  *	duplicated in all such forms and that any documentation,
  *	advertising materials, and other materials related to such
  *	distribution and use acknowledge that the software was developed
  *	by Swapneel Naphade. The name of the
  *	author may not be used to endorse or promote products derived
  *	from this software without specific prior written permission.
  *	THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
  *	IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
  ******************************************************************************
  */

#include "telemetry.h"

void TELEMETRY_config(uint32_t baudrate){
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

void TELEMETRY_send(char *buffer){
	while(*buffer)// Loop while there are more characters to send.
	{
		USART_SendData(USART1, *buffer++);//
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //wait for next character to send
	}
}
