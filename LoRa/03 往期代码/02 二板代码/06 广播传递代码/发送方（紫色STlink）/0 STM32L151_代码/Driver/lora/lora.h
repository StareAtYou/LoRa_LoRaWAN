#ifndef __LORA_H
#define __LORA_H	 

#include "sys.h"
#include "string.h"
#include "stdlib.h"
#include "general_type.h"
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"

//#define EN_Lora 		PBout(12)  AUX
//#define RolaM0 PBout(1)
//#define RolaM1 PBout(2)
extern u8 LORA_RecData[600];

void UART2_SendString(char* s);
void Lora_Init(void);
void E32_MODE_Control(unsigned int M0,unsigned int M1);
void LORA_Receive(void)	;
void LORA_Send(u8 *buf);

#endif

