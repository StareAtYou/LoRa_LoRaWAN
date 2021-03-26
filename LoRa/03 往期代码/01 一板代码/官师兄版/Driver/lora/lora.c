#include "lora.h"
#include "usart2.h"
#include "usart3.h"
u8 LORA_RecData[600];
/*-----------------------------------
函数功能：Lora控制引脚的初始化
函数参数：无
-------------------------------------*/
void Lora_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);	 //使能PB
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;				 //LED0-->PB. 1端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为2MHz
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
  //GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_2);						 //PB1
  GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_2);						 //PB1
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);						 //PB1
//	GPIO_SetBits(GPIOB,GPIO_Pin_2);						 //PB2
}



/*-------------------------------------------------
函数功能：Lora控制模块
 函数参数：无
--------------------------------------------------*/
void E32_MODE_Control(unsigned int M0,unsigned int M1)
{
	if(M0 == 0 && M1 == 0)//一般模式（模式 0）
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	else if(M0 == 1 && M1 == 0)//唤醒模式（模式 1）
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	else if(M0 == 0 && M1 == 1)//省电模式（模式 2）
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else if(M0 == 1 && M1 == 1)//休眠模式（模式 3）
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);	
	}	
}
/*-------------------------------------------------
函数功能：Lora数据的发送
函数参数：无
--------------------------------------------------*/
void LORA_Send(u8 *buf)
{
	USART3_OUT(USART2,buf,sizeof(buf));//向串口2发送数据
}
/*-------------------------------------------------
函数功能：Lora数据的存储
函数参数：无
--------------------------------------------------*/
void LORA_Receive()
{
		u16 i3,rxlen3;
		rxlen3=USART3_RX_STA&0X7FFF;	//得到数据长度
		for(i3=0;i3<rxlen3;i3++)
		{
		LORA_RecData[i3] = USART3_RX_BUF[i3];
	  }
		USART2_TX_BUF[rxlen3]=0;
		LORA_RecData[rxlen3]=0;			//自动添加结束符
		USART2_OUT(USART2,USART2_TX_BUF,sizeof(USART2_TX_BUF));
}

