#include "uart.h"
bit busy;

void Uart01_Init(void)		//9600bps@11.0592MHz
{

	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE0;		//设置定时初始值
	TH1 = 0xFE;		//设置定时初始值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时

    ES = 1;
    EA = 1;     //开启定时器
}

void Uart01_SendByte(u8 _data)
{
    SBUF = _data;
    while(TI == 0);
    TI = 0;
}

void Uart01_SendString(u8 *str)
{
	while(*str !='\0')		
		Uart01_SendByte(*str++);
}

void Uart02_Init()		//9600bps
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xE0;		//设置定时初始值
	T2H = 0xFE;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时

    IE2 &= 0xFE;   //先对需要设置的位进行清零 1111 1110
    IE2 |= 0x01;   // | ESPI | ES2 允许UART2中断
    EA = 1;        //允许总中断

	P_SW2 &=~ 0X01;	//选择 P10RX P11TX
}

/***********发送*********/
void Uart02_SendData(unsigned char dat)
{
    while (busy); // 等待前面的数据发送完成
    busy = 1;
    S2BUF = dat; // 写数据到UART2数据寄存器
}

/************发送字符串*******************/
void Uart02_SendString(char *s)
{
    while (*s) // 检测字符串结束标志
    {
        Uart02_SendData(*s++); // 发送当前字符
    }
}

