#include "BasicFun.h"
#include "uart.h"
#include "DHT11.h"
#include "LCD1602.h"

#define KEY1 P20
#define KEY2 P21
#define KEY3 P22
#define KEY4 P23
#define KEY5 P32
#define KEY6 P33
#define KEY7 P35

extern bit busy;

char *str01 = "Welcome";
char *str02 = "Start Menu";

u8 cur_work_mode = 0;

u8 cur_hour = 9;
u8 cur_min  = 0;
u8 cur_sec  = 0;

u8 adm_hour_up = 8;	//工作时间阈值  时 上限
u8 adm_min_up = 30;	//工作时间阈值  分 上限
u8 adm_hour_down = 23;	//工作时间阈值  时 下限
u8 adm_min_down = 30;	//工作时间阈值  分 下限

void sysInit()
{
	Timer0Init();
	LCD_Init();
	Uart01_Init();   //串口1初始化	
	Uart02_Init();	 //串口2初始化	
}

void LCD_ShowDoorContext()
{
	LCD_ShowString(1,1,str01);
	LCD_ShowString(2,1,str02);
}

void LCD_SetCurClockMode()
{
	LCD_ShowString(1,1,"CurTime:");
	LCD_ShowNum(1,9,cur_hour,2);
	LCD_ShowString(1,11,"-");
	LCD_ShowNum(1,12,cur_min,2);
	LCD_ShowString(1,14,"-");
	LCD_ShowNum(1,15,cur_sec,2);

	LCD_ShowString(2,1,"Set:");
	LCD_ShowNum(2,4,adm_hour_up,2);
	LCD_ShowString(2,6,"-");
	LCD_ShowNum(2,7,adm_min_up,2);
	LCD_ShowString(2,9,"--");

	LCD_ShowNum(2,11,adm_hour_down,2);
	LCD_ShowString(2,13,"-");
	LCD_ShowNum(2,14,adm_min_down,2);
}


u8 key_scan()
{
	u8 k = 0;
	if(KEY1==0)
	{
		delay_ms(15);
		if(KEY1==0)
		{
			k = 1;
		}
		while(!KEY1);
	}

	if(KEY2==0)
	{
		delay_ms(15);
		if(KEY2==0)
		{
			k = 2;
		}
		while(!KEY2);
	}

	if(KEY3==0)
	{
		delay_ms(15);
		if(KEY3==0)
		{
			k = 3;
		}
		while(!KEY3);
	}

	if(KEY4==0)
	{
		delay_ms(15);
		if(KEY4==0)
		{
			k = 4;
		}
		while(!KEY4);
	}

	if(KEY5==0)
	{
		delay_ms(15);
		if(KEY5==0)
		{
			k = 5;
		}
		while(!KEY5);
	}

	if(KEY6==0)
	{
		delay_ms(15);
		if(KEY6==0)
		{
			k = 6;
		}
		while(!KEY6);
	}

	if(KEY7==0)
	{
		delay_ms(15);
		if(KEY7==0)
		{
			k = 7;
		}
		while(!KEY7);
	}

	return k;

}

void main()
{
	u8 key_v = 0;
	u8 allow_flag = 1;
	
	sysInit();	 //开发板外设复位
	
	LCD_ShowDoorContext();

	while (1)
	{
		key_v = key_scan();

		if(key_v == 5)
		{
			LCD_Init();
			cur_work_mode = (cur_work_mode+1)%4;
		}
		
		if( (adm_hour_up*60 + adm_min_up < cur_hour*60 + cur_min) && (adm_hour_down*60 + adm_min_down > cur_hour*60 + cur_min) )
		{
			allow_flag = 1;
		}
		else
		{
			allow_flag = 0;
		}

		//显示来客
		if(allow_flag)
		{
			if(key_v == 1)
			{
				cur_work_mode = 0;
				LCD_Init();
//				str01 = "Come in";
//				str02 = "My dear";
				LCD_ShowString(1,1,"Come in");
				LCD_ShowString(2,1,"My dear");
				Uart01_SendString("A8:02/01*MP3");	
				Uart02_SendString("Come in,My dear!");
			}
			if(key_v == 2)
			{
				cur_work_mode = 0;
				LCD_Init();
//				str01 = "Come in";
//				str02 = "My frined";
				LCD_ShowString(1,1,"Come in");
				LCD_ShowString(2,1,"My frined");
				Uart01_SendString("A8:02/02*MP3");
				Uart02_SendString("Come in,My frined!");
			}
			if(key_v == 3)
			{
				cur_work_mode = 0;
				LCD_Init();
//				str01 = "Please wait";
//				str02 = "I will open soon";
				LCD_ShowString(1,1,"Please wait");
				LCD_ShowString(2,1,"I will open soon");
				Uart01_SendString("A8:02/03*MP3");
				Uart02_SendString("Please wait,I will open soon!");
			}
			if(key_v == 4)
			{
				cur_work_mode = 0;
				LCD_Init();
//				str01 = "Please wait";
//				str02 = "I will open soon";
				LCD_ShowString(1,1,"Please wait");
				LCD_ShowString(2,1,"I will open soon");
				Uart01_SendString("A8:02/04*MP3");
				Uart02_SendString("Please wait,I will open soon!");
			}
		}

		if( cur_work_mode==1 )		//设置当前闹钟
		{
			if(key_v == 6)
			{
				cur_hour = (cur_hour+1)%24;
			}

			if(key_v == 7)
			{
				cur_min = (cur_min+1)%60;
			}
		}
		else if( cur_work_mode==2 )		//设置允许工作闹钟区间
		{
			if(key_v == 6)
			{
				adm_hour_up = (adm_hour_up+1)%24;
			}

			if(key_v == 7)
			{
				adm_min_up = (adm_min_up+1)%60;
			}
		}
		else if( cur_work_mode==3 )		//设置允许工作闹钟区间
		{
			if(key_v == 6)
			{
				adm_hour_down = (adm_hour_down+1)%24;
			}

			if(key_v == 7)
			{
				adm_min_down = (adm_min_down+1)%60;
			}
		}



			
		
		if( cur_work_mode == 1 ||cur_work_mode == 2 ||cur_work_mode == 3)
			LCD_SetCurClockMode();
		
	}
}


void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    T0Count++;
    if(T0Count>=1000)
    {
        T0Count=0;
		cur_sec++;
    }

	if(cur_sec>=60)
	{
		cur_sec = 0;
		cur_min ++;
	}

	if(cur_min>=60)
	{
		cur_min = 0;
		cur_hour ++;
	}

	if(cur_hour>=24)
	{
		cur_hour = 0;
	}

}


void Uart01_Routine() interrupt 4
{
	u8 uart_data; //串口收到的数据
    if(RI == 1)
    {
        RI = 0;
        uart_data = SBUF;

    }
}

void Uart02_Routine() interrupt 8 using 2
{
    unsigned char mydata;
    if(S2CON & 0x01)          //如果是接收中断
    {
        S2CON &= 0xFE;       //接收中断标志位清0  
        mydata = S2BUF;      //将接收缓冲区的数据保存到mydata变量中

    }

	if(S2CON & 0x02)          //如果是发送中断
    {
        S2CON &= 0xFD;       //发送中断标志清0  
		busy = 0;
    }

}








