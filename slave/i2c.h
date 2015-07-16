/*
	I2C 头文件
*/

#ifndef __I2C_H__
#define __I2C_H__

#include <reg52.h>
#include <instrins.h>

void Start_I2C();
void Stop_I2C();
bit SendByte(unsigned char c);
unsigned char RcvByte();
void Ack_I2C();
void No_Ack_I2C();
bit ISendStr(unsigned char sla,unsigned char suba, unsigned char *s, unsigned char num);
bit IRcvStr(unsigned char sla, unsigned char suba, unsigned char *s, unsigned char num);

#endif
