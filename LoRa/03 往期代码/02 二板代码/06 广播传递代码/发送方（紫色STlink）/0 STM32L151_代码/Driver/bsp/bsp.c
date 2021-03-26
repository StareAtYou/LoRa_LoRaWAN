#include "bsp.h"

void bsp_init(void)
{
	delay_init(32);//时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	LED_Init();    //LED初始化
	KEY_Init();
	
	Lora_Init();
//	E32_MODE_Control(0,0);
	
	//OLED_Init();
	
	USART1_Configuration(9600);//蓝牙
	//USART2_Configuration(9600);//GPS
	USART3_Configuration(9600);//Lora通信
	
}
