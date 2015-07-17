#include "delay.h"
#include "tm7705.h"
// #include "i2c.h"
// #include "1602.h"
#include "uart.h"
#include <stdio.h>
#include <reg52.h>

unsigned char flag = 0;
unsigned short count = 0;
unsigned long rotation = 0;

void EX0_Init() {
	EA = 1;
	IT0 = 1;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = 0;
	TL0 = 0;
}

void EX0_ISR () interrupt 0 {
	if (flag == 0) {
		TR0 = 1;
		flag = 1;
	} 

	else if (flag == 1) {
		TR0 = 0;
		EX0 = 0;
		flag = 2;
	}
	
}

void Timer0_ISR() interrupt 1{
	count ++;
	TL0 = 0;
	TH0 = 0;
}

void main() {
	unsigned int adc1, adc2;
	UART_Init();
	TM7705_Init();
	EX0_Init();
	//自校准
	TM7705_CalibSelf(1);
	TM7705_CalibSelf(2);
	while(1){
		adc1 = TM7705_ReadAdc(1);
		adc2 = TM7705_ReadAdc(2);
		EX0 = 1;

		while(flag != 2);
		if (flag == 2) {
			EX0 = 0;
			flag = 0;
			count = 0;
			rotation = 65536 * count + 256 * TH0 + TL0;
		}

		//printf("CH1 = %04X, (%7.5f) V \t CH2 = %04X, (%7.5f) V \r\n", adc1, (adc1*5.0)/65535, adc2, (adc2*5.0)/65535);
		printf("%d \t %X \t %X \r\n", count, TH0, TL0);
		printf("rotation = %10.5f Hz \n", 1000000/(rotation * 0.9216));
	}
}

