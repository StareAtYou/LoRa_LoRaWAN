#include "key.h"
#include "general_type.h"
					    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);//使能PORTC

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;//KEY
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //设置成输入
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为2MHz
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC13
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0))
	{
		delay_ms(100);//去抖动 
		key_up=0;
		if(KEY0==0)
		return KEY0_PRES;
	}else if(KEY0==1)key_up=1; 	    
 	return 0;// 无按键按下
}
//判断是否误按
u8 KEY()
{
	u8 key_status;
	key_status=KEY_Scan(1);
	if(key_status) 
	{
		delay_ms(1000);
		if(key_status)
		return status;
	}
}

