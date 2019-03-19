/**
  ******************************************************************************
  * @file    sensor.c
  * @author  Swapneel Naphade
  * @version V1.0.0
  * @date    09-DEC-2017
  * @brief   This file contains all the functions definitions for the SENSOR firmware
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
  *	by Swapneel Naphade. The name of the
  *	author may not be used to endorse or promote products derived
  *	from this software without specific prior written permission.
  *	THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
  *	IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
  ******************************************************************************
  */
#include "sensor.h"


/******************  Conversion Function Definitions  ******************/
double SENSOR_ADC_Conversion_Function_Default(unsigned int val){
	return (double)val;
}


void SENSOR_DI_Init(uint16_t RCC_APB2Periph_GPIO, SENSOR_DIGITAL_INPUT_TypeDef* SENSOR_Struct){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = SENSOR_Struct->SENSOR_DIGITAL_INPUT_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(SENSOR_Struct->SENSOR_DIGITAL_INPUT_Port, &GPIO_InitStruct);
}

void SENSOR_ADC_Init(uint16_t RCC_APB2Periph_GPIO, uint16_t RCC_APB2Periph_ADC, SENSOR_ADC_TypeDef* SENSOR_Struct){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = SENSOR_Struct->SENSOR_ADC_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SENSOR_Struct->SENSOR_ADC_Port, &GPIO_InitStruct);
	//Initialize ADC1
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	// we work in continuous sampling mode
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;//initiate the number of used channel
	ADC_Init (ADC1, &ADC_InitStructure);	//set config of ADC1
	// enable ADC1
	ADC_Cmd (ADC1,ENABLE);
	// calibrate ADC1
	//	ADC calibration (optional, but recommended at power on)
	ADC_ResetCalibration(ADC1);	// Reset previous calibration
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);	// Start new calibration (ADC must be off at that time)
	while(ADC_GetCalibrationStatus(ADC1));
	SENSOR_Struct->SENSOR_ADC_Conversion_Function = SENSOR_ADC_Conversion_Function_Default; //Change this if your function is different
}


uint8_t GET_DI_SENSOR_Value(SENSOR_DIGITAL_INPUT_TypeDef *SENSOR_struct){
	return GPIO_ReadInputDataBit(SENSOR_struct->SENSOR_DIGITAL_INPUT_Port, SENSOR_struct->SENSOR_DIGITAL_INPUT_Pin);
}

unsigned int GET_ADC_SENSOR_Value(SENSOR_ADC_TypeDef *SENSOR_struct){
	ADC_RegularChannelConfig(ADC1,SENSOR_struct->SENSOR_ADC_Channel, 1,ADC_SampleTime_28Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADC1);
}














