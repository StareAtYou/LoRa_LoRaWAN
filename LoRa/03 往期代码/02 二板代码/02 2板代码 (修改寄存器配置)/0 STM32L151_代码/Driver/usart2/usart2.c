#include "usart2.h"
#include "pbdata.h"
#include "timer.h"

u8  USART2_RX_BUF[USART2_REC_LEN]; 				//���ջ���,���USART1_REC_LEN���ֽ�.
u8  USART2_TX_BUF[USART2_SEND_LEN]; 			//���ͻ���,���USART1_SEND_LEN�ֽ�
u16 USART2_RX_STA=0;       //����״̬���	

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
//   while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//�ȴ������������);
//   return ch;
//}

void USART2_Configuration(u32 baund)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	//GPIOAʱ��
    
	  //NVIC_Configuration();
	
 	  USART_DeInit(USART2);  //��λ����1
    
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
		
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//����USART2�Ľ����ж�
		//Usart1 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
		
		TIM6_Int_Init(99,7199);		//10ms�ж�
		USART2_RX_STA=0;		//����
		TIM_Cmd(TIM6,DISABLE);			//�رն�ʱ��7
		
		USART_ClearFlag(USART2,USART_FLAG_TC); //���������ɱ�־λ 
		
}


void USART2_IRQHandler(void)                	//����1�жϷ������
	{
	u8 res2;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		res2 =USART_ReceiveData(USART2);	//��ȡ���յ�������
			if((USART2_RX_STA&(1<<15))==0)//����δ���
			{
			if(USART2_RX_STA<USART2_REC_LEN)	//�����Խ�������
				{
				TIM_SetCounter(TIM6,0);//��������� 
				if(USART2_RX_STA==0) 				//ʹ�ܶ�ʱ��7���ж� 
				{
					TIM_Cmd(TIM6,ENABLE);//ʹ�ܶ�ʱ��7
				}
				USART2_RX_BUF[USART2_RX_STA++]=res2;	//��¼���յ���ֵ
				}
				else
					{
					USART2_RX_STA|=1<<15;				//ǿ�Ʊ�ǽ������
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
	i=strlen((const char*)USART2_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}






