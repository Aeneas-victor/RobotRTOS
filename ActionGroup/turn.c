#include "Action.h"
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : turn.c
  * @brief          : 转弯动作组
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
uint8_t turn_part[12]=
{
	frontLeft_leg,frontLeft_joint,middleLeft_leg,middleLeft_joint,rearLeft_leg,rearLeft_joint,
	rearRight_leg,rearRight_joint,middleLeft_leg,middleRight_joint,frontRight_leg,frontRight_joint
};
uint8_t turn_joint[6]=
{
	frontLeft_joint,middleLeft_joint,rearLeft_joint,rearRight_joint,middleRight_joint,frontLeft_joint
};

void Turn_func()
{
	
}


