#ifndef __UART_H_
#include "BasicFun.h"



void Uart01_Init(void);
void Uart01_SendByte(u8 _data);
void Uart01_SendString(u8 *str);

void Uart02_Init();
void Uart02_SendData(unsigned char dat);
void Uart02_SendString(char *s);

#endif // !__UART_H_



