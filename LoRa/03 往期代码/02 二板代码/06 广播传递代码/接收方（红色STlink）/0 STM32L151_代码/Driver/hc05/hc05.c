//#include "usart1.h" 			 		 
//#include "hc05.h" 
//#include "pbdata.h"
// 
////��ʼ��ATK-HC05ģ��
////����ֵ:0,�ɹ�;1,ʧ��.
//u8 HC05_Init(void)
//{
//u8 retry=10,t;	  		 
//u8 temp=1;

//GPIO_InitTypeDef GPIO_InitStructure;

//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);	//ʹ��PORTA

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 // �˿�����
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 		 //�������
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;		 //IO���ٶ�Ϊ50MHz
//GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
//GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
//GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA8

//GPIO_SetBits(GPIOA,GPIO_Pin_4);
//// 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
////HC05_EN=1; 

////Usart1_Init(9600);	//��ʼ������1Ϊ:9600,������.

//while(retry--)
//{
//	HC05_EN=1;					//KEY�ø�,����ATģʽ
//	delay_ms(10);
//	u1_printf("AT\r\n");		//����AT����ָ��
//	HC05_EN=0;					//KEY����,�˳�ATģʽ
//	for(t=0;t<10;t++) 			//��ȴ�50ms,������HC05ģ��Ļ�Ӧ
//	{
//		if(USART1_RX_STA&0X8000)break;
//		delay_ms(5);
//	}		
//	if(USART1_RX_STA&0X8000)	//���յ�һ��������
//	{
//		temp=USART1_RX_STA&0X7FFF;	//�õ����ݳ���
//		USART1_RX_STA=0;			 
//		if(temp==4&&USART1_RX_BUF[0]=='O'&&USART1_RX_BUF[1]=='K')
//		{
//			temp=0;//���յ�OK��Ӧ
//			break;
//		}
//	}			    		
//}		    
//if(retry==0)temp=1;	//���ʧ��
//return temp;	  
//}	 
////��ȡATK-HC05ģ��Ľ�ɫ
////����ֵ:0,�ӻ�;1,����;0XFF,��ȡʧ��.							  
//u8 HC05_Get_Role(void)
//{	 		    
//	u8 retry=0X0F;
//	u8 temp,t;
//	while(retry--)
//	{
//		HC05_EN=1;					//KEY�ø�,����ATģʽ
//		delay_ms(10);
//		u1_printf("AT+ROLE?\r\n");	//��ѯ��ɫ
//		for(t=0;t<20;t++) 			//��ȴ�200ms,������HC05ģ��Ļ�Ӧ
//		{
//			delay_ms(10);
//			if(USART1_RX_STA&0X8000)break;
//		}		
//		HC05_EN=0;					//KEY����,�˳�ATģʽ
//		if(USART1_RX_STA&0X8000)	//���յ�һ��������
//		{
//			temp=USART1_RX_STA&0X7FFF;	//�õ����ݳ���
//			USART1_RX_STA=0;			 
//			if(temp==13&&USART1_RX_BUF[0]=='+')//���յ���ȷ��Ӧ����
//			{
//				temp=USART1_RX_BUF[6]-'0';//�õ�����ģʽֵ
//				break;
//			}
//		}		
//	}
//	if(retry==0)temp=0XFF;//��ѯʧ��.
//	return temp;
//} 							   

////ATK-HC05��������
////�˺�����������ATK-HC05,�����ڽ�����OKӦ���ATָ��
////atstr:ATָ�.����:"AT+RESET"/"AT+UART=9600,0,0"/"AT+ROLE=0"���ַ���
////����ֵ:0,���óɹ�;����,����ʧ��.							  
//u8 HC05_Set_Cmd(u8* atstr)
//{	 		    
//	u8 retry=0X0F;
//	u8 temp,t;
//	while(retry--)
//	{
//		HC05_EN=1;					//KEY�ø�,����ATģʽ
//		delay_ms(10);
//		u1_printf("%s\r\n",atstr);	//����AT�ַ���
//		HC05_EN=0;					//KEY����,�˳�ATģʽ
//		for(t=0;t<20;t++) 			//��ȴ�100ms,������HC05ģ��Ļ�Ӧ
//		{
//			if(USART1_RX_STA&0X8000)break;
//			delay_ms(5);
//		}		
//		if(USART1_RX_STA&0X8000)	//���յ�һ��������
//		{
//			temp=USART1_RX_STA&0X7FFF;	//�õ����ݳ���
//			USART1_RX_STA=0;			 
//			if(temp==4&&USART1_RX_BUF[0]=='O')//���յ���ȷ��Ӧ����
//			{			
//				temp=0;
//				break;			 
//			}
//		}		
//	}
//	if(retry==0)temp=0XFF;//����ʧ��.
//	return temp;
//} 	 											    






