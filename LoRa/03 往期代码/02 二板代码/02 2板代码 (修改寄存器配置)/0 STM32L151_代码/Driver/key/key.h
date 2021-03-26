#ifndef __KEY_H
#define __KEY_H	

#include "sys.h"
#include "general_type.h"
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "delay.h"

#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//读取按键0
#define KEY0_PRES 	1	//KEY0按下
#define status 	1//状态

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数	
u8 KEY();
#endif
