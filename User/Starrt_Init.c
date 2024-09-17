/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Start_Init
  * @brief          : program init
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024- aeneas-杨金鹏
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE BEGIN Header */
#include "stm32f10x.h"
#include "sys.h"
#include "SysTick.h"
#include "PCA9685.h"
#include "servo.h"
#include "Timer.h"
#include "Motor.h"
#include "Action.h"

extern const uint8_t Angle_Init[16];
extern uint8_t Angle_Start[16];
void Start_Init()
{
	for(uint8_t i=0;i<16;i++)
	{
		Angle_Start[i]=Angle_Init[i];
	}
}

