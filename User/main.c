/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : 主程序代码
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
#include <string.h>
#include "sys.h"
#include "SysTick.h"
#include "system.h"
#include "PCA9685.h"
#include "FreeRTOS_Action.h"
#include "servo.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Timer.h"
#include "Motor.h"
#include "Action.h"
#include "OLED.h"
#include "semphr.h"
#include "usart.h"
uint8_t Angle_Start[16];

TaskHandle_t StartTaxk_Handle;
void start_task(void* pvParameters);
TaskHandle_t front_left,front_right,middle_left,middle_right,rear_left,rear_right;
extern void Start_Init(void);
// right A1
// left A0

uint8_t KeyNum = 0;

int main(void)
{
	// test();
	// test2();
	SysTick_Init(72);
	OLED_Init();
	PCA9685_Init(50, 180);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	USART1_Init(115200);
	Start_Init();
	//    printf("AT+NAME\r\n");      //查询蓝牙名字
	//    Delay_ms(100);test

	Timer_Init();
	while (1)
	{
		standnormal();
		if (TIM2_IQRHandler() == 1)
			break;
	}
	Delay_ms(1500);
	taskENTER_CRITICAL();
	xTaskCreate(front_left_func,"front_left",512,NULL,1,&front_left);
	xTaskCreate(front_right_func,"front_right",512,NULL,1,&front_right);
	xTaskCreate(middle_left_func,"middle_left",512,NULL,1,&middle_left);
	xTaskCreate(middle_right_func,"middle_right",512,NULL,1,&middle_right);
	xTaskCreate(rear_left_func,"rear_left",256,NULL,1,&rear_left);
	xTaskCreate(rear_right_func,"rear_right",256,NULL,1,&rear_right);
	vTaskStartScheduler();
	vTaskDelete(StartTaxk_Handle);
	taskEXIT_CRITICAL();
	while (1)
	{
		//		standnormal();
		// CrouchMove();
		// AdvanceSingleWalk();
		//_Meanwhile_Advance_Move();
	}
}
