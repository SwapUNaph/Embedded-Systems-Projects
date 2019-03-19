/**
  ******************************************************************************
  * @file    main.c
  * @author  Swapneel Naphade
  * @version V1.0.0
  * @date    10-DEC-2017
  * @brief   This file contains telemetry functions declaration firmware
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
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"

void TELEMETRY_config(uint32_t baudrate);
void TELEMETRY_send(char *buffer);












