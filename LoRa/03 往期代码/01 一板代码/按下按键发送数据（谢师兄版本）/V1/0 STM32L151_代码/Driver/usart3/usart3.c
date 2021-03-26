#include "usart3.h"
#include "pbdata.h"
#include "timer.h"

u8  USART3_RX_BUF[USART3_REC_LEN]; 				//接收缓冲,最大USART1_REC_LEN个字节.
u8  USART3_TX_BUF[USART3_SEND_LEN]; 			//发送缓冲,最大USART1_SEND_LEN字节
u16 USART3_RX_STA=0;       //接收状态标记	

void USART3_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len)
{ 
	uint16_t i;
	for(i=0; i<Len; i++){
		USART_SendData(USARTx, Data[i]);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
	}
}

int fputc(int ch,FILE *f)
{
   USART_SendData(USART3,(u8)ch);
   while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);//等待发送数据完毕);
   return ch;
}

void USART3_Configuration(u32 baund)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);	//GPIOB时钟
    
	  //NVIC_Configuration();
	
 	  USART_DeInit(USART3);  //复位串口1
    
	 //USART3_TX   PB.10  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    

	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
    
    
    USART_InitStructure.USART_BaudRate = baund;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3,&USART_InitStructure);
		
    USART_Cmd(USART3,ENABLE);
		
		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//开启USART3的接收中断
		//Usart1 NVIC 配置
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口3中断通道
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
		
		USART_ClearFlag(USART3,USART_FLAG_TC); //清除发送完成标志位 
		
}


void USART3_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 res3;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		res3 =USART_ReceiveData(USART3);	//读取接收到的数据
		
		if((USART3_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART3_RX_STA&0x4000)//接收到了0x0d
				{
				if(res3!=0x0a)USART3_RX_STA=0;//接收错误,重新开始
				else USART3_RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(res3==0x0d)USART3_RX_STA|=0x4000;
				else
					{
					USART3_RX_BUF[USART3_RX_STA&0X7FFF]=res3 ;
					USART3_RX_STA++;
					if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
     } 
	 }
	
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}



	




