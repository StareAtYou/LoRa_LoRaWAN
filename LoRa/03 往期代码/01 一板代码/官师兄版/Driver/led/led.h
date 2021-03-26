#ifndef __LED_H
#define __LED_H	 

#include "sys.h"
#include "general_type.h"
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "delay.h"

void LED_Init(void);//³õÊ¼»¯
void LED(void);
#define LED0 GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_9)// PB9

//#define LED1_PORT 1
//#define LED1_RUN(sts) (sts?( GPIOA->ODR |= (unsigned int)(1<<LED1_PORT) ):( GPIOA->ODR &= ~((unsigned int)(1<<LED1_PORT) )))


#endif

















