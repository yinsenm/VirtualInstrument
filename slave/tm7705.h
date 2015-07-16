/*
	模块名称 : TM7705 驱动模块(2通道带PGA的16位ADC)
*/

#ifndef __TM7705_H_
#define __TM7705_H_

void TM7705_Init();
void TM7705_CalibSelf(unsigned char _ch);
void TM7705_SytemCalibZero(unsigned char _ch);
void TM7705_SytemCalibFull(unsigned char _ch);
unsigned short TM7705_ReadAdc(unsigned char _ch);

void TM7705_WriteReg(unsigned char _RegID, unsigned long _RegValue);
unsigned long TM7705_ReadReg(unsigned char _RegID);

#endif
