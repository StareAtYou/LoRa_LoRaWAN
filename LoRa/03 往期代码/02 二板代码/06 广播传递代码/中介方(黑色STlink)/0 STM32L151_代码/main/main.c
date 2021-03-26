#include "bsp.h"
#include "lora.h"
#include "usart3.h"
#include "pbdata.h"
#include "timer.h"
#include "usart1.h"

nmea_msg gpsx; 	//GPS��Ϣ
nmea_msg lorax;
char  buff1[600];//����GPSģ��������ݵĻ���
char  buff2[600];//����LORaģ��������ݵĻ���

u8 usart1_recdata[12];

__align(4) u8 dtbuf1[50];   	
__align(4) u8 dtbuf2[50];




void GPS_SHOW(void)
{
	float longitude,latitude,altitude,speed;
	OLED_ShowString(0,0,"GPS receive:",12,1);
	longitude= gpsx.longitude/100000;//����
	latitude = gpsx.latitude /100000;//γ��
	altitude = gpsx.altitude /10;		 //�߶�
	speed		 = gpsx.speed    /1000;	 //�ٶ�
	sprintf((char *)dtbuf1,"Longitude:%.5f %1c   ",longitude,gpsx.ewhemi);
	OLED_ShowString(0,10,dtbuf1,12,1);	//��ʾ����
	sprintf((char *)dtbuf1,"Latitude:%.5f %1c   ",latitude,gpsx.nshemi);	
	OLED_ShowString(0,20,dtbuf1,12,1);	//��ʾγ��
	sprintf((char *)dtbuf1,"Altitude:%.1fm     ",altitude);	    		
	OLED_ShowString(0,30,dtbuf1,12,1);  //��ʾ�߶�
	sprintf((char *)dtbuf1,"UTC Date:%04d/%02d/%02d   ",gpsx.utc.year,gpsx.utc.month,gpsx.utc.date);	
	OLED_ShowString(0,40,dtbuf1,12,1);  //��ʾUTC����
	sprintf((char *)dtbuf1,"UTC Time:%02d:%02d:%02d   ",gpsx.utc.hour,gpsx.utc.min,gpsx.utc.sec);	
	OLED_ShowString(0,50,dtbuf1,12,1);  //��ʾUTCʱ��
	
	OLED_Refresh();
}

void LORA_SHOW(void)
{
	float lora_longitude,lora_latitude,lora_altitude,lora_speed;
	OLED_ShowString(0,0,"LORA receive:",12,1);
	lora_longitude= lorax.longitude/100000;//����
	lora_latitude = lorax.latitude /100000;//γ��
	lora_altitude = lorax.altitude /10;		 //�߶�
	lora_speed		 = lorax.speed    /1000;	 //�ٶ�
	sprintf((char *)dtbuf2,"Longitude:%.5f %1c   ",lora_longitude,lorax.ewhemi);
	OLED_ShowString(0,10,dtbuf2,12,1);	//��ʾ����
	sprintf((char *)dtbuf2,"Latitude:%.5f %1c   ",lora_latitude,lorax.nshemi);	
	OLED_ShowString(0,20,dtbuf2,12,1);	//��ʾγ��
	sprintf((char *)dtbuf2,"Altitude:%.1fm     ",lora_altitude);	    		
	OLED_ShowString(0,30,dtbuf2,12,1);  //��ʾ�߶�
	sprintf((char *)dtbuf2,"UTC Date:%04d/%02d/%02d   ",lorax.utc.year,lorax.utc.month,lorax.utc.date);	
	OLED_ShowString(0,40,dtbuf2,12,1);  //��ʾUTC����
	sprintf((char *)dtbuf2,"UTC Time:%02d:%02d:%02d   ",lorax.utc.hour,lorax.utc.min,lorax.utc.sec);	
	OLED_ShowString(0,50,dtbuf2,12,1);  //��ʾUTCʱ��
	
		
	OLED_Refresh();
		
}


void LORA_SEND_tousart(void)
{
	float lora_longitude,lora_latitude,lora_altitude;
	lora_longitude= lorax.longitude/100000;//����
	lora_latitude = lorax.latitude /100000;//γ��
	lora_altitude = lorax.altitude /10;		 //�߶�
	sprintf((char *)buff2,
	" Longitude:%.5f %1c\r\n Latitude:%.5f %1c\r\n Altitude:%.1fm\r\n UTC Date:%04d/%02d/%02d\r\n UTC Time:%02d:%02d:%02d\r\n ",
	lora_longitude,lorax.ewhemi,lora_latitude,lorax.nshemi,lora_altitude,lorax.utc.year,lorax.utc.month,lorax.utc.date,lorax.utc.hour,lorax.utc.min,lorax.utc.sec);

	USART2_OUT(USART2,buff2,sizeof(buff2));
}

int main(void)
{ 
	u8 key;
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
	u8 rebroadcast_mode[]={0xc0,0x00,0x09,0xff,0xff,0x08,0x62,0x00,0x14,0x0b,0x00,0x00};
	
												

	bsp_init();		
//	OLED_Clear();
	
	E32_MODE_Control(0, 1);
	delay_ms(100);
	
//	USART3_OUT(USART3,open_relay,sizeof(open_relay));
//	delay_ms(50);
//  USART3_OUT(USART3,open_relay,sizeof(open_relay));
	
											
	for(i=0;i<3;i++)
	{
		USART3_OUT(USART3,broadcast_mode,sizeof(broadcast_mode));
		delay_ms(50);
	}

  	delay_ms(500);   //���úüĴ���������Ҫ500ms���ӳٲ����л�ģʽ������Ĵ���������Ч
		E32_MODE_Control(0, 0);
	  delay_ms(500);
	
	
	while(1)
	{
		  //USART3_OUT(USART3,usart1_recdata,sizeof(usart1_recdata));
		  //delay_ms(2000);
		
			//LED();
		//u3_printf("hello\r\n");
		//����
//		key=KEY();
		
		//����GPS�¼�
//		if(key)
//		{
//			OLED_Clear();
			//LED();
		
		
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
		//GPIO_SetBits(GPIOA,GPIO_Pin_2);
		
		  if(USART3_RX_STA&0x8000)
			{
					GPIO_ResetBits(GPIOA,GPIO_Pin_2);
					//delay_ms(500);
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
			
//			if(LORA_RecData[0] == 0xC0)
//					{
//							E32_MODE_Control(0, 1);
//							delay_ms(100);
//																	
//							for(i=0;i<3;i++)
//							{
//								USART3_OUT(USART3,rebroadcast_mode,sizeof(rebroadcast_mode));
//								delay_ms(50);
//							}
//							
//							delay_ms(500);   //���úüĴ���������Ҫ500ms���ӳٲ����л�ģʽ������Ĵ���������Ч
//							E32_MODE_Control(0, 0);
//							delay_ms(500);
//							
//							USART3_OUT(USART3,LORA_RecData,sizeof(LORA_RecData));
//					}
//		}			
	}	
}





















