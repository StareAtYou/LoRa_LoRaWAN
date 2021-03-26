#include "usart3.h"
#include "pbdata.h"
#include "timer.h"
#include "lora.h"

u8  USART3_RX_BUF[USART3_REC_LEN]; 				//���ջ���,���USART1_REC_LEN���ֽ�.
u8  USART3_TX_BUF[USART3_SEND_LEN]; 			//���ͻ���,���USART1_SEND_LEN�ֽ�
u16 USART3_RX_STA=0;       //����״̬���	
u8 rebroadcast_mode[]={0xc0,0x00,0x09,0xff,0xff,0x08,0x62,0x00,0x14,0x0b,0x00,0x00};
u8 broadcast_mode[]={0xc0,0x00,0x09,0xff,0xff,0x08,0x62,0x00,0x17,0x0b,0x00,0x00};
u8 example[] = {0xB0,0x01,0x02,0x03};

void USART3_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len)
{ 
	uint16_t i;
	for(i=0; i<Len; i++){
		USART_SendData(USARTx, Data[i]);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	}
}

int fputc(int ch,FILE *f)
{
   USART_SendData(USART3,(u8)ch);
   while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);//�ȴ������������);
   return ch;
}

void USART3_Configuration(u32 baund)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);	//GPIOBʱ��
    
	  //NVIC_Configuration();
	
 	  USART_DeInit(USART3);  //��λ����1
    
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
		
		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//����USART3�Ľ����ж�
		//Usart1 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����3�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
		
		USART_ClearFlag(USART3,USART_FLAG_TC); //���������ɱ�־λ 
		
}


void USART3_IRQHandler(void)                	//����1�жϷ������
	{
	u8 res3;
	int i;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		res3 =USART_ReceiveData(USART3);	//��ȡ���յ�������
		
		if(res3 == 0xA0)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_2);
			E32_MODE_Control(0, 1);
			delay_ms(100);
													
			for(i=0;i<3;i++)
			{
				USART3_OUT(USART3,rebroadcast_mode,sizeof(rebroadcast_mode));
				delay_ms(50);
			}
			
			delay_ms(500);   //���úüĴ���������Ҫ500ms���ӳٲ����л�ģʽ������Ĵ���������Ч
			E32_MODE_Control(0, 0);
			delay_ms(500);
			
			USART3_OUT(USART3,example,sizeof(example));
			
			delay_ms(500);
			E32_MODE_Control(0, 1);
			delay_ms(100);
													
			for(i=0;i<3;i++)
			{
				USART3_OUT(USART3,broadcast_mode,sizeof(broadcast_mode));
				delay_ms(50);
			}
			
			delay_ms(500);   //���úüĴ���������Ҫ500ms���ӳٲ����л�ģʽ������Ĵ���������Ч
			E32_MODE_Control(0, 0);
			delay_ms(500);
			
			GPIO_SetBits(GPIOA,GPIO_Pin_2);
		}
		
			
		
		if((USART3_RX_STA&0x8000)==0)//����δ���
			{
			if(USART3_RX_STA&0x4000)//���յ���0x0d
				{
				if(res3!=0x0a)USART3_RX_STA=0;//���մ���,���¿�ʼ
				else USART3_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(res3==0x0d)USART3_RX_STA|=0x4000;
				else
					{
					USART3_RX_BUF[USART3_RX_STA&0X7FFF]=res3 ;
					USART3_RX_STA++;
					if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
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
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}



	




