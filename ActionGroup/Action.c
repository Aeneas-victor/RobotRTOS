/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Action.c
  * @brief          : 运动的规则函数文件
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
#include "PCA9685.h"
#include "servo.h"
#include "Action.h"
#include "Timer.h"
void (*MoveTemplete)(void);

const uint8_t body[16]={
				//后腿
				rearRight_foot,rearLeft_foot,
				rearRight_leg,rearLeft_leg,
				rearRight_joint,rearLeft_joint,
				//中腿
				middleRight_foot,middleLeft_foot,
				middleRight_leg,middleLeft_leg,
				middleRight_joint,middleLeft_joint,
				//前腿
				frontRight_joint,frontLeft_joint,
				frontRight_leg,frontLeft_leg
};
uint8_t Alone_Servo[2]={30,150};//0L 1R
const uint8_t standAngle[16]={//站立姿态枚举
	180,0,150,30, //3
    60,60,175,0, //7
    130,40,70,110,//11
	60,40,175,0//15
};
const uint8_t Angle_Init[16]=
{
	140,20,60,90,
	100,95,145,20,
	60,90,90,85,//11
	55,110,30,100
};
extern uint8_t Angle_Start[16];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int8_t AlternatingTripodGait_advanceLeft_Uplift[6]=//左腿移动抬起角度枚举
{
/////10,100,100,60,30,
  -30,-10,30,20,-30,-20,
// 15,13,8,10,3,5
};
int8_t AlternatingTripodGait_advanceLeft_LayDown[6]=//左腿移动放下角度枚举
{
	0,30,0, -20,0,20
////70,60,50,100,80
////
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


uint8_t AlternatingTripodGait_advanceLeftMoveModule[6]=//左腿移动的零部件枚举
{
	frontLeft_leg,frontLeft_joint,middleRight_leg,middleRight_joint,rearLeft_leg,rearLeft_joint
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int8_t AlternatingTripodGait_advanceRight_Uplift[6]=//右腿移动抬起角度枚举
{
	30,10,-30,-20,30,20
////14,12,9,11,2,4
};
int8_t AlternatingTripodGait_advanceRight_LayDown[6]=//右腿移动放下角度枚举
{
	0,-30,0,20,0,-20
////40,110,85,70,40
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


uint8_t AlternatingTripodGait_advanceRightMoveModule[6]=//右腿移动零部件枚举
{
	frontRight_leg,frontRight_joint,middleLeft_leg,middleLeft_joint,rearRight_leg,rearRight_joint
};



/** _move_Toleg(uint8_t* bodyModule,int8_t* ModuleAngle)
  * @brief  一次同时改变6个连接处的角度变化
  * @param  uint8_t* bodyModule  腿部零部件枚举uint8_t 数组
  * @param  int8_t* ModuleAngle  移动角度枚举 int8_t 数组
  * @retval  无
  */
void _move_Toleg(uint8_t* bodyModule,int8_t* ModuleAngle)
{
	for(uint8_t i=0;i<6;i++)
	{
		setAngle(bodyModule[i],Angle_Start[bodyModule[i]]+ModuleAngle[i]);
		
	}
}
uint8_t SingleWalkMove_Module[12]=
{
	frontLeft_leg,frontLeft_joint,frontRight_leg,frontRight_joint,
	middleLeft_leg,middleLeft_joint,middleRight_leg,middleRight_joint,
	rearLeft_leg,rearLeft_joint,rearRight_leg,rearRight_joint
};
int8_t SingleWalkMove_advance_Uplift[12]=
{
	-30,-10,30,10,-30,-20,30,20,-30,-20,30,20
};
int8_t SingleWalkMove_advance_LayDown[12]=
{
	0,30,0,-30,0,20,0,-20,0,20,0,-20
};

void AdvanceSingleWalk(void)
{
	setAngle(SingleWalkMove_Module[0],Angle_Start[SingleWalkMove_Module[0]]-30);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[1],Angle_Start[SingleWalkMove_Module[1]]-10);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[0],Angle_Start[SingleWalkMove_Module[0]]);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[1],Angle_Start[SingleWalkMove_Module[1]]+30);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[2],Angle_Start[SingleWalkMove_Module[2]]+30);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[3],Angle_Start[SingleWalkMove_Module[3]]+10);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[2],Angle_Start[SingleWalkMove_Module[2]]);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[3],Angle_Start[SingleWalkMove_Module[3]]-30);
	Delay_ms(200);
	
	setAngle(SingleWalkMove_Module[4],Angle_Start[SingleWalkMove_Module[4]]-30);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[5],Angle_Start[SingleWalkMove_Module[5]]-20);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[4],Angle_Start[SingleWalkMove_Module[4]]);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[5],Angle_Start[SingleWalkMove_Module[5]]+20);
	Delay_ms(200);
	
	setAngle(SingleWalkMove_Module[6],Angle_Start[SingleWalkMove_Module[6]]+30);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[7],Angle_Start[SingleWalkMove_Module[7]]+20);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[6],Angle_Start[SingleWalkMove_Module[6]]);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[7],Angle_Start[SingleWalkMove_Module[7]]-20);
	Delay_ms(200);
	
	setAngle(SingleWalkMove_Module[8],Angle_Start[SingleWalkMove_Module[8]]-30);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[9],Angle_Start[SingleWalkMove_Module[9]]-20);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[8],Angle_Start[SingleWalkMove_Module[8]]);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[9],Angle_Start[SingleWalkMove_Module[9]]+20);
	Delay_ms(200);
	
	setAngle(SingleWalkMove_Module[10],Angle_Start[SingleWalkMove_Module[10]]+30);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[11],Angle_Start[SingleWalkMove_Module[11]]+20);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[10],Angle_Start[SingleWalkMove_Module[10]]);
	Delay_ms(200);
	setAngle(SingleWalkMove_Module[11],Angle_Start[SingleWalkMove_Module[11]]-20);
	Delay_ms(200);
	

//	for(uint8_t i=0;i<6;i++)
//	{
//		for(uint8_t j=0;j<2;j++)
//		{
//			int8_t *Module_angle;
//			if(i/2==0)
//			{
//				Module_angle=SingleWalkMove_advance_Uplift;
//			}
//			else Module_angle=SingleWalkMove_advance_LayDown;
//			setAngle(SingleWalkMove_Module[i*2+j],Angle_Start[SingleWalkMove_Module[i]]+Module_angle[i*2+j]);
//			Delay_ms(200);
//		}
//	}
}
void AdvanceMove(void)
{
	Timer_Init();
	while(1)
	{
		_move_Toleg(AlternatingTripodGait_advanceLeftMoveModule,AlternatingTripodGait_advanceLeft_Uplift);
		if(TIM2_IQRHandler()==1)
		{
			break;
		}
	}
	Timer_Init();
	while(1)
	{
		_move_Toleg(AlternatingTripodGait_advanceLeftMoveModule,AlternatingTripodGait_advanceLeft_LayDown);
		if(TIM2_IQRHandler()==1)
		{
		break;
		}
	}
	Timer_Init();
	while(1)
	{
		_move_Toleg(AlternatingTripodGait_advanceRightMoveModule,AlternatingTripodGait_advanceRight_Uplift);
		if(TIM2_IQRHandler()==1)
		{
		break;
		}
	}
	Timer_Init();

	while(1)
	{
		_move_Toleg(AlternatingTripodGait_advanceRightMoveModule,AlternatingTripodGait_advanceRight_LayDown);
		if(TIM2_IQRHandler()==1)
		{
			break;
		}
	}

}

void _Meanwhile_Advance_Move()
{
	Timer_Init();
	while(1)
	{
		_move_Toleg(AlternatingTripodGait_advanceRightMoveModule,AlternatingTripodGait_advanceRight_LayDown);
		Delay_ms(5);
		_move_Toleg(AlternatingTripodGait_advanceLeftMoveModule,AlternatingTripodGait_advanceLeft_Uplift);//左腿抬起
		Delay_ms(5);
		if(TIM2_IQRHandler()==1)
			break;
	}
	Delay_ms(5);
	Timer_Init();
	while(1)
	{
		_move_Toleg(AlternatingTripodGait_advanceLeftMoveModule,AlternatingTripodGait_advanceLeft_LayDown);//左腿放下
		Delay_ms(5);
		_move_Toleg(AlternatingTripodGait_advanceRightMoveModule,AlternatingTripodGait_advanceRight_Uplift);//右腿抬起
		Delay_ms(5);
		if(TIM2_IQRHandler()==1)
			break;
	}
	Delay_ms(5);
	//ServoLegLeft_SetAngle(Alone_Servo[0]);
	//ServoLegRight_SetAngle(Alone_Servo[1]);
	//Delay_ms(100);
}
uint8_t CrouchUpMove_Module[10]=
{
	middleLeft_foot,frontLeft_leg,middleLeft_leg,rearLeft_foot,rearLeft_leg,
	middleRight_foot,frontRight_leg,middleRight_leg,rearRight_foot,rearRight_leg
};

void CrouchUp(void)
{
	int8_t angle=20;
	for(uint8_t i=0;i<10;i++)
	{
		if(i>5)
			angle=-20;
		setAngle(CrouchUpMove_Module[i],Angle_Start[CrouchUpMove_Module[i]]+angle);
	}
	
}

void CrouchDown(void)
{
	int8_t angle=-20;
	for(uint8_t i=0;i<10;i++)
	{
		if(i>5)
			angle=20;
		setAngle(CrouchUpMove_Module[i],Angle_Start[CrouchUpMove_Module[i]]+angle);
	}
}

void CrouchMove(void)
{
	Timer_Init();
	while(1)
	{
		CrouchUp();
		if(TIM2_IQRHandler()==1)
		{
			break;
		}
	}
	Delay_ms(500);
	Timer_Init();
	while(1)
	{
		CrouchDown();
		if(TIM2_IQRHandler()==1)
		{
			break;
		}
	}
}
void normal(const uint8_t* action)
{
	ServoLegLeft_SetAngle(Alone_Servo[0]);
	ServoLegRight_SetAngle(Alone_Servo[1]);
	//Delay_ms(100);
	for(uint8_t i=0;i<16;i++)
	{
		setAngle(body[i],action[i]);
		//Delay_ms(100);
	}
}
void standnormal(void)
{
	normal(Angle_Start);
}


