#ifndef __KEY_H
#define __KEY_H	

#include "sys.h"
#include "general_type.h"
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "delay.h"

#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//��ȡ����0
#define KEY0_PRES 	1	//KEY0����
#define status 	1//״̬

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��	
u8 KEY(void);
#endif
