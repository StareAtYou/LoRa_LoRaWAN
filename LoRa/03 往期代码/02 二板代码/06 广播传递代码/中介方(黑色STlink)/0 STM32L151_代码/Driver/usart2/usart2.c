#include "usart2.h"
#include "pbdata.h"
#include "timer.h"

u8  USART2_RX_BUF[USART2_REC_LEN]; 				//接收缓冲,最大USART1_REC_LEN个字节.
u8  USART2_TX_BUF[USART2_SEND_LEN]; 			//发送缓冲,最大USART1_SEND_LEN字节
u16 USART2_RX_STA=0;       //接收状态标记	

void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len)
{ 
	uint16_t i;
	for(i=0; i<Len; i++){
		USART_SendData(USARTx, Data[i]);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	}
}
//int fputc(int ch,FILE *f)
//{
//   USART_SendData(USART2,(u8)ch);
//   while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//等待发送数据完毕);
//   return ch;
//}

void USART2_Configuration(u32 baund)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	//GPIOA时钟
    
	  //NVIC_Configuration();
	
 	  USART_DeInit(USART2);  //复位串口1
    
	 //USART2_TX   PA.2  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
    
    
    USART_InitStructure.USART_BaudRate = baund;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2,&USART_InitStructure);
		
    USART_Cmd(USART2,ENABLE);
		
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开启USART2的接收中断
		//Usart1 NVIC 配置
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口2中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
		
		TIM6_Int_Init(99,7199);		//10ms中断
		USART2_RX_STA=0;		//清零
		TIM_Cmd(TIM6,DISABLE);			//关闭定时器7
		
		USART_ClearFlag(USART2,USART_FLAG_TC); //清除发送完成标志位 
		
}


void USART2_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 res2;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		res2 =USART_ReceiveData(USART2);	//读取接收到的数据
			if((USART2_RX_STA&(1<<15))==0)//接收未完成
			{
			if(USART2_RX_STA<USART2_REC_LEN)	//还可以接收数据
				{
				TIM_SetCounter(TIM6,0);//计数器清空 
				if(USART2_RX_STA==0) 				//使能定时器7的中断 
				{
					TIM_Cmd(TIM6,ENABLE);//使能定时器7
				}
				USART2_RX_BUF[USART2_RX_STA++]=res2;	//记录接收到的值
				}
				else
					{
					USART2_RX_STA|=1<<15;				//强制标记接收完成
					}		 
				}   		 
     } 
}

	
void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}






