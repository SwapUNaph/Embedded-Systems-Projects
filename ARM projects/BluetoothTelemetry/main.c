/**
  ******************************************************************************
  * @file    main.c
  * @author  Swapneel Naphade
  * @version V1.0.0
  * @date    09-DEC-2017
  * @brief   This file contains main firmware
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


#include "sensor.h"
#include "telemetry.h"
#include "stdio.h"
#include "string.h"

void GPIO_config(void);
void num_to_str(char *, double);
void wait(unsigned long);

int main(void){

	SENSOR_ADC_TypeDef Light_sensor;
	Light_sensor.SENSOR_ADC_Pin = GPIO_Pin_2;
	Light_sensor.SENSOR_ADC_Channel=ADC_Channel_2;
	Light_sensor.SENSOR_ADC_Port = GPIOA;
	SENSOR_ADC_Init(RCC_APB2Periph_GPIOA, RCC_APB2Periph_ADC1, &Light_sensor);

	SENSOR_DIGITAL_INPUT_TypeDef Button;
	Button.SENSOR_DIGITAL_INPUT_Pin = GPIO_Pin_11;
	Button.SENSOR_DIGITAL_INPUT_Port = GPIOB;
	SENSOR_DI_Init(RCC_APB2Periph_GPIOB, &Button);
	TELEMETRY_config(115200);
	GPIO_config();
	TELEMETRY_send("----------------\n\nHello! I am stm32f103c8...\n\n------------------\n\n");
	char numstr[64];
	int button;
	unsigned int adcval;
    while(1)
    {
    	adcval = GET_ADC_SENSOR_Value(&Light_sensor);
    	button = GET_DI_SENSOR_Value(&Button);
    	sprintf(numstr, "%d, %d,\n",adcval,button);
    	TELEMETRY_send(numstr);
    	GPIO_SetBits(GPIOC, GPIO_Pin_13);
    	wait(1000000);
    	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    }
}

void GPIO_config(void){

	//ENABLE GPIOA | GPIOC | USART CLOCK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	//INITIALIZE PIN C13 TO OUTPUT
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOC, &gpio);
}


void wait(unsigned long cycles){
	while(cycles--){}
}

void num_to_str(char *str, double num){
	char *sign = (num < 0)? "-" : "" ;
	num = (num < 0)? -num : num;
	int mantissa = num;// Get the integer (678).
	double decimal = num - mantissa;
	int decint = decimal*10000;
	sprintf (str, "%s%d.%04d", sign, mantissa, decint);
}

