#include "bsp.h"


nmea_msg gpsx; 	//GPS信息
nmea_msg lorax;
char  buff1[600];//接收GPS模块解析数据的缓存
char  buff2[600];//接收LORa模块解析数据的缓存
__align(4) u8 dtbuf1[50];   	
__align(4) u8 dtbuf2[50]; 

u8 test_buf[600];
u8 buf[600];
char buff[600];


void GPS_SHOW(void)
{
	float longitude,latitude,altitude,speed;
	OLED_ShowString(0,0,"GPS receive:",12,1);
	longitude= gpsx.longitude/100000;//经度
	latitude = gpsx.latitude /100000;//纬度
	altitude = gpsx.altitude /10;		 //高度
	speed		 = gpsx.speed    /1000;	 //速度
	sprintf((char *)dtbuf1,"Longitude:%.5f %1c   ",longitude,gpsx.ewhemi);
	OLED_ShowString(0,10,dtbuf1,12,1);	//显示经度
	sprintf((char *)dtbuf1,"Latitude:%.5f %1c   ",latitude,gpsx.nshemi);	
	OLED_ShowString(0,20,dtbuf1,12,1);	//显示纬度
	sprintf((char *)dtbuf1,"Altitude:%.1fm     ",altitude);	    		
	OLED_ShowString(0,30,dtbuf1,12,1);  //显示高度
	sprintf((char *)dtbuf1,"UTC Date:%04d/%02d/%02d   ",gpsx.utc.year,gpsx.utc.month,gpsx.utc.date);	
	OLED_ShowString(0,40,dtbuf1,12,1);  //显示UTC日期
	sprintf((char *)dtbuf1,"UTC Time:%02d:%02d:%02d   ",gpsx.utc.hour,gpsx.utc.min,gpsx.utc.sec);	
	OLED_ShowString(0,50,dtbuf1,12,1);  //显示UTC时间
	
	OLED_Refresh();
}

void LORA_SHOW(void)
{
	float lora_longitude,lora_latitude,lora_altitude,lora_speed;
	OLED_ShowString(0,0,"LORA receive:",12,1);
	lora_longitude= lorax.longitude/100000;//经度
	lora_latitude = lorax.latitude /100000;//纬度
	lora_altitude = lorax.altitude /10;		 //高度
	lora_speed		 = lorax.speed    /1000;	 //速度
	sprintf((char *)dtbuf2,"Longitude:%.5f %1c   ",lora_longitude,lorax.ewhemi);
	OLED_ShowString(0,10,dtbuf2,12,1);	//显示经度
	sprintf((char *)dtbuf2,"Latitude:%.5f %1c   ",lora_latitude,lorax.nshemi);	
	OLED_ShowString(0,20,dtbuf2,12,1);	//显示纬度
	sprintf((char *)dtbuf2,"Altitude:%.1fm     ",lora_altitude);	    		
	OLED_ShowString(0,30,dtbuf2,12,1);  //显示高度
	sprintf((char *)dtbuf2,"UTC Date:%04d/%02d/%02d   ",lorax.utc.year,lorax.utc.month,lorax.utc.date);	
	OLED_ShowString(0,40,dtbuf2,12,1);  //显示UTC日期
	sprintf((char *)dtbuf2,"UTC Time:%02d:%02d:%02d   ",lorax.utc.hour,lorax.utc.min,lorax.utc.sec);	
	OLED_ShowString(0,50,dtbuf2,12,1);  //显示UTC时间
	
		
	OLED_Refresh();
		
}


void LORA_SEND_tousart(void)
{
	float lora_longitude,lora_latitude,lora_altitude;
	lora_longitude= lorax.longitude/100000;//经度
	lora_latitude = lorax.latitude /100000;//纬度
	lora_altitude = lorax.altitude /10;		 //高度
	sprintf((char *)buff2,
	" Longitude:%.5f %1c\r\n Latitude:%.5f %1c\r\n Altitude:%.1fm\r\n UTC Date:%04d/%02d/%02d\r\n UTC Time:%02d:%02d:%02d\r\n ",
	lora_longitude,lorax.ewhemi,lora_latitude,lorax.nshemi,lora_altitude,lorax.utc.year,lorax.utc.month,lorax.utc.date,lorax.utc.hour,lorax.utc.min,lorax.utc.sec);

	USART2_OUT(USART2,buff2,sizeof(buff2));
}

int main(void)
{ 
	u8 key;
	u8 len3,len2,i;

	bsp_init();		
	//OLED_Clear();

	while(1)
	{
		LED();
		
		//按键
		//key=KEY();
		
		/*
		//处理GPS事件
		//if(key)
		//{
			//OLED_Clear();
			//LED();
			if((USART2_RX_STA&0X8000))
			{
				len2=USART2_RX_STA&0X7FFF;
		    for(i=0;i<len2;i++)
		   {
			  GPS_RecData[i]=USART2_RX_BUF[i];
		   }
		    GPS_RecData[len2]=0;
	    	USART2_OUT(USART3,GPS_RecData,sizeof(GPS_RecData));
		  	GPS_Analysis(&gpsx,(u8*)GPS_RecData);//分析字符串
			GPS_SHOW(); //显示GPS 解析数据
			USART2_RX_STA=0;		   	//启动下一次接收
			}		
		//}
		*/
	
		
		//else 
		//{ 
		//处理蓝牙事件
		//if(USART1_RX_STA&0X8000)
		//{
		//	Blue_receive();
		//	USART1_RX_STA=0;
		//}
		
			if((USART2_RX_STA&0X8000))
			{
				len2=USART2_RX_STA&0X7FFF;
		    for(i=0;i<len2;i++)
		   {
			  test_buf[i]=USART2_RX_BUF[i];
		   }
		    test_buf[len2]=0;
	    	USART2_OUT(USART3,test_buf,sizeof(test_buf));
		  	//GPS_Analysis(&gpsx,(u8*)GPS_RecData);//分析字符串
			//GPS_SHOW(); //显示GPS 解析数据
			USART2_RX_STA=0;		   	//启动下一次接收
		 }
		
		 /*
		//处理接收到求救信号事件
		  if(USART3_RX_STA&0x8000)
			{
			len3=USART3_RX_STA&0X7FFF;	//得到数据长度
			for(i=0;i<len3;i++)
			{
				LORA_RecData[i]=USART3_RX_BUF[i];
	    }
			LORA_RecData[len3]=0;
			GPS_Analysis(&lorax,(u8*)LORA_RecData);
			LORA_SEND_tousart();
			LORA_SHOW();
			USART3_RX_STA=0;
		  }
		 */
			
			//处理接收到求救信号事件
		  if(USART3_RX_STA&0x8000)
			{
			len3=USART3_RX_STA&0X7FFF;	//得到数据长度
			for(i=0;i<len3;i++)
			{
				buf[i]=USART3_RX_BUF[i];
	    } 
			buf[len3]=0;
			
			sprintf((char *)buff,"%s\r\n", buf);    
			u3_printf("%s\r\n", buff); 
			u2_printf("%s", buff);  //直接通过串口2打印输出到串口助手显示
			//USART3_OUT(USART2,buff,sizeof(buff));
			//USART2_RX_STA=0;   
			
			//GPS_Analysis(&lorax,(u8*)LORA_RecData);
			//LORA_SEND_tousart();
			//LORA_SHOW();
			USART3_RX_STA=0;
		  }
		}			
	//}	
}
