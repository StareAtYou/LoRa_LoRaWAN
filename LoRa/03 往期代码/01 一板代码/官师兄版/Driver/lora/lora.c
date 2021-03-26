#include "lora.h"
#include "usart2.h"
#include "usart3.h"
u8 LORA_RecData[600];
/*-----------------------------------
�������ܣ�Lora�������ŵĳ�ʼ��
������������
-------------------------------------*/
void Lora_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);	 //ʹ��PB
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;				 //LED0-->PB. 1�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO���ٶ�Ϊ2MHz
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
  //GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_2);						 //PB1
  GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_2);						 //PB1
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);						 //PB1
//	GPIO_SetBits(GPIOB,GPIO_Pin_2);						 //PB2
}



/*-------------------------------------------------
�������ܣ�Lora����ģ��
 ������������
--------------------------------------------------*/
void E32_MODE_Control(unsigned int M0,unsigned int M1)
{
	if(M0 == 0 && M1 == 0)//һ��ģʽ��ģʽ 0��
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	else if(M0 == 1 && M1 == 0)//����ģʽ��ģʽ 1��
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	else if(M0 == 0 && M1 == 1)//ʡ��ģʽ��ģʽ 2��
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else if(M0 == 1 && M1 == 1)//����ģʽ��ģʽ 3��
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);	
	}	
}
/*-------------------------------------------------
�������ܣ�Lora���ݵķ���
������������
--------------------------------------------------*/
void LORA_Send(u8 *buf)
{
	USART3_OUT(USART2,buf,sizeof(buf));//�򴮿�2��������
}
/*-------------------------------------------------
�������ܣ�Lora���ݵĴ洢
������������
--------------------------------------------------*/
void LORA_Receive()
{
		u16 i3,rxlen3;
		rxlen3=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
		for(i3=0;i3<rxlen3;i3++)
		{
		LORA_RecData[i3] = USART3_RX_BUF[i3];
	  }
		USART2_TX_BUF[rxlen3]=0;
		LORA_RecData[rxlen3]=0;			//�Զ���ӽ�����
		USART2_OUT(USART2,USART2_TX_BUF,sizeof(USART2_TX_BUF));
}

