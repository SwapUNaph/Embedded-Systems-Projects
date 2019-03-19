/**
  ******************************************************************************
  * @file    sensor.h
  * @author  Swapneel Naphade
  * @version V1.0.0
  * @date    09-DEC-2017
  * @brief   This file contains all the functions prototypes for the SENSOR firmware
  * library of BluetoothTelemetry project.
  ******************************************************************************
  *	Copyright (c) 2017, Swapneel Naphade.
  *	All rights reserved.
  *
  *	Redistribution and use in source and binary forms are permitted
  *	provided that the above copyright notice and this paragraph are
  *	duplicated in all such forms and that any documentation,
  *	advertising materials, and other materials related to such
  *	distribution and use acknowledge that the software was developed
  *	by the Swapneel Naphade. The name of the
  *	author may not be used to endorse or promote products derived
  *	from this software without specific prior written permission.
  *	THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
  *	IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
  ******************************************************************************
  */


#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"


typedef struct{
	uint8_t SENSOR_ADC_Channel;
	uint16_t SENSOR_ADC_Pin;
	GPIO_TypeDef* SENSOR_ADC_Port;
	double (*SENSOR_ADC_Conversion_Function)(unsigned int val);
	unsigned int SENSOR_Value;
}SENSOR_ADC_TypeDef;

typedef struct{
	uint16_t SENSOR_DIGITAL_INPUT_Pin;
	GPIO_TypeDef* SENSOR_DIGITAL_INPUT_Port;
	uint8_t SENSOR_Value;
}SENSOR_DIGITAL_INPUT_TypeDef;

typedef struct{
	uint16_t SENSOR_I2C_Pin;
	GPIO_TypeDef* SENSOR_Port;
	double (*SENSOR_Conversion_Function)(unsigned int val);
	unsigned int (*GET_I2C_SENSOR_Value)(void);
	unsigned int SENSOR_Value;
}SENSOR_I2C_TypeDef;

void SENSOR_ADC_Init(uint16_t RCC_APB2Periph_GPIO, uint16_t RCC_APB2Periph_ADC, SENSOR_ADC_TypeDef* SENSOR_Struct);
void SENSOR_DI_Init(uint16_t RCC_APB2Periph_GPIO, SENSOR_DIGITAL_INPUT_TypeDef* SENSOR_Struct);
void SENSOR_I2C_Init(uint32_t RCC_APB2Periph_GPIO, uint32_t RCC_APB2Periph_I2C, SENSOR_I2C_TypeDef* SENSOR_Struct);
unsigned int GET_ADC_SENSOR_Value(SENSOR_ADC_TypeDef* SENSOR_struct);
uint8_t GET_DI_SENSOR_Value(SENSOR_DIGITAL_INPUT_TypeDef* SENSOR_struct);
