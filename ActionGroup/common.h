#ifndef __COMMON_H__
#define __COMMON_H__
#include<stdint.h>
typedef void(*front_Leg)(float);
enum Body{
	rearRight_foot=0,rearLeft_foot,//1
	rearRight_leg,rearLeft_leg,//3
	rearRight_joint,rearLeft_joint,//5
	
	middleRight_foot,middleLeft_foot,//7
	middleRight_leg,middleLeft_leg,//9
	middleRight_joint,middleLeft_joint,//11
	
	frontRight_joint,frontLeft_joint,//13
	frontRight_leg,frontLeft_leg//15
	
};






#endif
