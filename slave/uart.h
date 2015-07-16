/*
	串口头文件
*/

#ifndef __UART_H__
#define __UART_H__

void UART_Init();
void UART_SendByte(unsigned char _data);
unsigned char UART_GetByte();
void UART_SendStr(unsigned char *str, unsigned char len);

#endif