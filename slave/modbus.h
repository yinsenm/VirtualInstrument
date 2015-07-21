/*
	Modbus 串口通信协议头文件
*/

#ifndef __MODBUS_H__
#define __MODBUS_H__

void MODBUS(unsigned int *pData, unsigned int addr, unsigned int frc);
unsigned int LRC(unsigned int *pData, unsigned int addr, unsigned int frc);

#endif
