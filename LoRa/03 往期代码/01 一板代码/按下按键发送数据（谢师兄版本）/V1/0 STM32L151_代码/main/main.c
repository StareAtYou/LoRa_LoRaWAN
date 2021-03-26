#include "bsp.h"
#include "key.h"
#include "lora.h"
#include "usart3.h"
#include "pbdata.h"
#include "timer.h"
#include "usart1.h"
#include "led.h"

int main(void)
{ 
	u8 len3=0;
	u8 i=0;
	delay_init(32);//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	KEY_Init();
	LED_Init();
	USART3_Configuration(9600);
	USART_Cmd(USART3,ENABLE);
	Lora_Init();
	E32_MODE_Control(0, 0);
	
	while(1)
	{
		if(KEY())
			USART3_OUT(USART3,(u8 *)"hello_node1\r\n",13);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		delay_ms(1000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		delay_ms(1000);
		if(USART3_RX_STA&0x8000)
		{
				len3=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
				for(i=0;i<len3;i++)
				{
					LORA_RecData[i]=USART3_RX_BUF[i];
				}
				LORA_RecData[len3]='\n';
				USART3_OUT(USART3,LORA_RecData,sizeof(LORA_RecData));
				USART3_RX_STA=0;
		}
	}
	/*u8 key;
	u8 len1,len3,len2,i;
	u8 read_register[]={0xc1,0x00,0x07};
	u8 open_relay[]={0xc0,0x06,0x01,0x23};
	u8 close_relay[]={0xc0,0x06,0x01,0x03};
	
	u8 configure_Init[]={0xc0,    //��ȡ�Ĵ���ָ��
												0x00,   //��ȡ��ַ��ʼλ
												0x09,   //��ȡ�Ĵ�����ַ����
												0x00,
												0x42,   //ģ���ַ����   66
												0x08,   //����ID����    8
												0x62,   //���ڲ����ʣ�У��λ�����߿����ٶ�������
												0x00,   //�ְ����ã�RSSI��������ʹ�ܣ����书������
												0x17,   //�ŵ�����   23
												0x03,   //RSSI�ֽڣ����䷽ʽ���м̹��ܣ�LBTʹ�ܣ�WORģʽ��WOR��������
												0x00,0x00  //��Կ��/���ֽ�����
											};
	
	u8 broadcast_mode[]={0xc0,0x00,0x09,0xff,0xff,0x08,0x62,0x00,0x17,0x0b,0x00,0x00};
	u8 example_send[] = {0xA0,0x01,0x02,0x03};
												
	//0xc0 0x00 0x09 0x00 0x42 0x08 0x62 0x00 0x17 0x03 0x00 0x00
	//0xc0 0x00 0x09 0x00 0x42 0x08 0x62 0x00 0x17 0x23 0x00 0x00

	bsp_init();		
//	OLED_Clear();
	
	E32_MODE_Control(0, 1);
	delay_ms(100);
	
//	USART3_OUT(USART3,open_relay,sizeof(open_relay));
//	delay_ms(50);
//  USART3_OUT(USART3,open_relay,sizeof(open_relay));
	
											
	for(i=0;i<3;i++)
	{
		//USART3_OUT(USART3,configure_Init,sizeof(configure_Init));
		USART3_OUT(USART3,broadcast_mode,sizeof(broadcast_mode));
		delay_ms(50);
	}

  	
	  delay_ms(500);   //���úüĴ���������Ҫ500ms���ӳٲ����л�ģʽ������Ĵ���������Ч
		E32_MODE_Control(0, 0);
	  delay_ms(500);

	while(1)
	{
		
		if(KEY())
		{
			USART3_OUT(USART3,example_send,sizeof(example_send));
			LED();
			
		}
		
		//LED();
			//USART1_OUT(USART3,broadcast_mode,sizeof(broadcast_mode));
		  //u3_printf("\n");
		  //delay_ms(3000);
		
			
		//u3_printf("hello\r\n");
		//����
//		key=KEY();
		
		//����GPS�¼�
//		if(key)
//		{
//			OLED_Clear();
//			LED();
		
		
			if((USART1_RX_STA&0X8000))
			{
				len1=USART1_RX_STA&0X7FFF;
		    for(i=0;i<len1;i++)
		   {
					usart1_recdata[i]=USART1_RX_BUF[i];
		   }
		    usart1_recdata[len1]=0;
	    	USART1_OUT(USART3,usart1_recdata,sizeof(usart1_recdata));
				USART1_OUT(USART1,usart1_recdata,sizeof(usart1_recdata));
//		  GPS_Analysis(&gpsx,(u8*)GPS_RecData);//�����ַ���
//			GPS_SHOW(); //��ʾGPS ��������
				USART1_RX_STA=0;		   	//������һ�ν���
			}
		
		
//			if((USART2_RX_STA&0X8000))
//			{
//				len2=USART2_RX_STA&0X7FFF;
//		    for(i=0;i<len2;i++)
//		   {
//					GPS_RecData[i]=USART2_RX_BUF[i];
//		   }
//		    GPS_RecData[len2]=0;
//	    	USART2_OUT(USART3,GPS_RecData,sizeof(GPS_RecData));
////		  	GPS_Analysis(&gpsx,(u8*)GPS_RecData);//�����ַ���
////			GPS_SHOW(); //��ʾGPS ��������
//				USART2_RX_STA=0;		   	//������һ�ν���
//			}		
//		}
		
//		else 
//		{             
		//���������¼�
//		if(USART1_RX_STA&0X8000)
//		{
//			Blue_receive();
//			USART1_RX_STA=0;
//		}
		
		//������յ�����ź��¼�
		  if(USART3_RX_STA&0x8000)
			{
					len3=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
					for(i=0;i<len3;i++)
					{
						LORA_RecData[i]=USART3_RX_BUF[i];
					}
					LORA_RecData[len3]=0;
					//GPS_Analysis(&lorax,(u8*)LORA_RecData);
					//LORA_SEND_tousart();
					//LORA_SHOW();
					USART3_OUT(USART3,LORA_RecData,sizeof(LORA_RecData));
					USART3_RX_STA=0;
		  }
//		}			
	}	*/
}





















