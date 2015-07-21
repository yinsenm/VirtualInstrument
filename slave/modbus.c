/*
	Modbus 串口通信协议
*/
#include "modbus.h"
#include <stdio.h>
void MODBUS(unsigned int *pData, unsigned int addr, unsigned int frc) {
	unsigned char i;
	unsigned int lrc;
	lrc = LRC(pData, addr, frc);
	printf(":");
	printf("%02X%02X", addr, frc);
	for (i = 0; i < 4; i++) {
		printf("%04X", pData[i]);
	}
	printf("%02X\r\n", lrc);
}

unsigned int LRC(unsigned int *pData, unsigned int addr, unsigned int frc) {
	unsigned int lrc = 0;
	unsigned char i;
	lrc = lrc + (addr + frc);
	for (i = 0; i < 4; i++) {
		lrc = lrc + (pData[i] / 256) + (pData[i] % 256);
	}
	return ((~lrc) + 1);
}

