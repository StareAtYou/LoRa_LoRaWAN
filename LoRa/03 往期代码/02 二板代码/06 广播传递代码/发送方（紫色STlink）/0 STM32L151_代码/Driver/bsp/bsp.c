#include "bsp.h"

void bsp_init(void)
{
	delay_init(32);//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	LED_Init();    //LED��ʼ��
	KEY_Init();
	
	Lora_Init();
//	E32_MODE_Control(0,0);
	
	//OLED_Init();
	
	USART1_Configuration(9600);//����
	//USART2_Configuration(9600);//GPS
	USART3_Configuration(9600);//Loraͨ��
	
}
