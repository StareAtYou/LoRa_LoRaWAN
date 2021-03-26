#include "usart1.h"
#include "pbdata.h"
#include "timer.h"

u8  USART1_RX_BUF[USART1_REC_LEN]; 				//���ջ���,���USART1_REC_LEN���ֽ�.
u8  USART1_TX_BUF[USART1_SEND_LEN]; 			//���ͻ���,���USART1_SEND_LEN�ֽ�
u16 USART1_RX_STA=0;       //����״̬���	

void USART1_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len)
{ 
	uint16_t i;
	for(i=0; i<Len; i++){
		USART_SendData(USARTx, Data[i]);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	}
}

//int fputc(int ch,FILE *f)
//{
//   USART_SendData(USART1,(u8)ch);
//   while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ������������);
//   return ch;
//}

void USART1_Configuration(u32 baund)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART1
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	//GPIOAʱ��
    
	  //NVIC_Configuration();
	
 	  USART_DeInit(USART1);  //��λ����1
    
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	 //USART2_TX   PA.9  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
		
    USART_InitStructure.USART_BaudRate = baund;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1,&USART_InitStructure);
		
    USART_Cmd(USART1,ENABLE);
		
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//����USART1�Ľ����ж�
		//Usart1 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
		
		TIM7_Int_Init(99,7199);		//10ms�ж�
		USART1_RX_STA=0;		//����
		TIM_Cmd(TIM7,DISABLE);			//�رն�ʱ��7
		USART_ClearFlag(USART1,USART_FLAG_TC); //���������ɱ�־λ 
		
}

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 res1;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		res1 =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		if((USART1_RX_STA&(1<<15))==0)//����δ���
			{
			if(USART1_RX_STA<USART1_REC_LEN)	//�����Խ�������
				{
				TIM_SetCounter(TIM7,0);//��������� 
				if(USART1_RX_STA==0) 				//ʹ�ܶ�ʱ��7���ж� 
				{
					TIM_Cmd(TIM7,ENABLE);//ʹ�ܶ�ʱ��7
				}
				USART1_RX_BUF[USART1_RX_STA++]=res1;	//��¼���յ���ֵ
				}
				else
					{
					USART1_RX_STA|=1<<15;				//ǿ�Ʊ�ǽ������
					}		 
				}
			}   		 
}

void u1_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART1_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART1_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART1,USART1_TX_BUF[j]); 
	} 
}






