#include "FreeRTOS_Action.h"
#include "FreeRTOS.h"
#include "SysTick.h"
#include "task.h"
#include "PCA9685.h"
#include "semphr.h"
#include "common.h"
#include "Timer.h"
extern const uint8_t body[16];
extern TaskHandle_t StartTaxk_Handle;
extern uint8_t Angle_Start[16];
extern TaskHandle_t front_left,front_right,middle_left,middle_right,rear_left,rear_right;

SemaphoreHandle_t xMutex;
void front_left_func(void* pvParameters)//one
{
	while(1)
	{
		if(xSemaphoreTake(xMutex,portMAX_DELAY)==pdTRUE)
		{
			Timer_Init();
			while(1)
			{
				setAngle(frontLeft_leg,Angle_Start[frontLeft_leg]-30);
				setAngle(frontLeft_joint,Angle_Start[frontLeft_joint]-10);
				if(TIM2_IQRHandler()==1)
					break;
			}
			Timer_Init();
			while(1)
			{
				setAngle(frontLeft_leg,Angle_Start[frontLeft_leg]);
				setAngle(frontLeft_joint,Angle_Start[frontLeft_joint]+30);
				if(TIM2_IQRHandler()==1)
					break;
			}
			xSemaphoreGive(xMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(1));
	}
	
}

void front_right_func(void* pvParameters)//two
{
	vTaskDelay(100);
	while(1)
	{
		if(xSemaphoreTake(xMutex,portMAX_DELAY)==pdTRUE)
		{
			Timer_Init();
			while(1)
			{
				setAngle(frontRight_leg,Angle_Start[frontRight_leg]+30);
				setAngle(frontRight_joint,Angle_Start[frontRight_joint]+10);
				if(TIM2_IQRHandler()==1)
					break;
			}
			Timer_Init();
			while(1)
			{
				setAngle(frontRight_leg,Angle_Start[frontRight_leg]);
				setAngle(frontRight_joint,Angle_Start[frontRight_joint]-30);
				if(TIM2_IQRHandler()==1)
					break;
			}
			xSemaphoreGive(xMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(1));
	}
}

void middle_left_func(void* pvParameters)//three
{
	vTaskDelay(200);
	while(1)
	{
		if(xSemaphoreTake(xMutex,portMAX_DELAY)==pdTRUE)
		{
			Timer_Init();
			while(1)
			{
				setAngle(middleLeft_leg,Angle_Start[middleLeft_leg]-30);
				setAngle(middleLeft_joint,Angle_Start[middleLeft_joint]-10);
				if(TIM2_IQRHandler()==1)
					break;
			}
			Timer_Init();
			while(1)
			{
				setAngle(middleLeft_leg,Angle_Start[middleLeft_leg]);
				setAngle(middleLeft_joint,Angle_Start[middleLeft_joint]+20);
				if(TIM2_IQRHandler()==1)
					break;
			}
			xSemaphoreGive(xMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(1));
	}
}

void middle_right_func(void* pvParameters)//four
{
	vTaskDelay(300);
	while(1)
	{
		if(xSemaphoreTake(xMutex,portMAX_DELAY)==pdTRUE)
		{
			Timer_Init();
			while(1)
			{
				setAngle(middleRight_leg,Angle_Start[middleRight_leg]+30);
				setAngle(middleRight_joint,Angle_Start[middleRight_joint]+20);
				if(TIM2_IQRHandler()==1)
					break;
			}
			Timer_Init();
			while(1)
			{
				setAngle(middleRight_leg,Angle_Start[middleRight_leg]);
				setAngle(middleRight_joint,Angle_Start[middleRight_joint]-20);
				if(TIM2_IQRHandler()==1)
					break;
			}
				xSemaphoreGive(xMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(1));
	}
}

void rear_left_func(void* pvParameters)//five
{
	vTaskDelay(400);
	while(1)
	{
		if(xSemaphoreTake(xMutex,portMAX_DELAY)==pdTRUE)
		{
			Timer_Init();
			while(1)
			{
				setAngle(rearLeft_leg,Angle_Start[rearLeft_leg]-30);
				setAngle(rearLeft_joint,Angle_Start[rearLeft_joint]-20);
				if(TIM2_IQRHandler()==1)
					break;
			}
			Timer_Init();
			while(1)
			{
				setAngle(rearLeft_leg,Angle_Start[rearLeft_leg]);
				setAngle(rearLeft_joint,Angle_Start[rearLeft_joint]+20);
				if(TIM2_IQRHandler()==1)
					break;
			}
				xSemaphoreGive(xMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(1));
	}
	
}

void rear_right_func(void* pvParameters)//six
{
	vTaskDelay(500);
	while(1)
	{
		if(xSemaphoreTake(xMutex,portMAX_DELAY)==pdTRUE)
		{
			Timer_Init();
			while(1)
			{
				setAngle(rearRight_leg,Angle_Start[rearRight_leg]+30);
				setAngle(rearRight_joint,Angle_Start[rearRight_joint]+20);
				if(TIM2_IQRHandler()==1)
					break;
			}
			Timer_Init();
			while(1)
			{
				setAngle(rearRight_leg,Angle_Start[rearRight_leg]);
				setAngle(rearRight_joint,Angle_Start[rearRight_joint]-20);
				if(TIM2_IQRHandler()==1)
					break;
			}
			xSemaphoreGive(xMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(1));
	}
}
