#include "led.h"
#include "general_type.h"

void LED_Init(void)
{
    
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB, GPIO_Pin_9);       	
}

void LED(void)
{
			GPIO_ResetBits(GPIOB,GPIO_Pin_9);		
			delay_ms(200);
			GPIO_SetBits(GPIOB,GPIO_Pin_9);
			//delay_ms(1000);	//—” ±100ms	
}



