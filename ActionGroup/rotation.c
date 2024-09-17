#include "Action.h"
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : rotation.c
  * @brief          : 旋转动作组
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-aeneas
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

#include "PCA9685.h"
#include "servo.h"
#include "Action.h"
#include "Timer.h"
extern uint8_t body[16];
extern uint8_t Alone_Servo[2];
extern uint8_t standAngle[16];
extern const uint8_t Angle_Init[16];
extern uint8_t Angle_Start[16];
uint8_t rotation_joint[6]=
{
	frontLeft_joint,middleLeft_joint,rearLeft_joint,rearRight_joint,middleRight_joint,frontRight_joint
};

void Roration_place(uint8_t direction)//暂设定旋转20°
{//0 left /////// 1 right
	int8_t angle=direction==0?20:-20;
	for(uint8_t i=0;i<6;i++)
	{
		Angle_Start[rotation_joint[i]]=Angle_Start[rotation_joint[i]]+angle;
	}
}
