/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           :servo.c
  * @brief          : 单独舵机控制模块函数
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-/////版权所有人
  *
  ******************************************************************************
  */
/* USER CODE BEGIN Header */

#include "stm32f10x.h"                  // Device header
#include "PWM.h"
 
void Servo_Init(void)
{
	PWM_Init();
}
void ServoLegRight_SetAngle(float Angle2)//A1//right
{
	PWM_SetCompare2(Angle2 / 180 * 2000 + 500);
 
}
void ServoLegLeft_SetAngle(float Angle1)//A0//left
{
	PWM_SetCompare1(Angle1 / 180 * 2000 + 500);
 
}

