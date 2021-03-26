#include "key.h"
#include "general_type.h"
					    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);//ʹ��PORTC

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;//KEY
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //���ó�����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO���ٶ�Ϊ2MHz
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC13
}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0))
	{
		delay_ms(100);//ȥ���� 
		key_up=0;
		if(KEY0==0)
		return KEY0_PRES;
	}else if(KEY0==1)key_up=1; 	    
 	return 0;// �ް�������
}
//�ж��Ƿ���
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

