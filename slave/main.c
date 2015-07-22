#include "delay.h"
#include "tm7705.h"
// #include "i2c.h"
// #include "1602.h"
#include "uart.h"
#include "modbus.h"
#include <stdio.h>
#include <reg52.h>

#define ADDR 0x03

unsigned char ex0_flag = 0; //外部中断INT0的中断标志，2次中断后开始计时
unsigned char cal_flag = 0; //计算标志位，标志为1时开始计算
unsigned int count = 0;

void EX0_Init() {
	EA = 1;
	IT0 = 1;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = 0;
	TL0 = 0;
	EX0 = 1;
	ET0 = 1;
}

void EX0_ISR () interrupt 0 {
	ex0_flag++;
	if(ex0_flag == 2) {
		TR0 =~ TR0; //开启关闭定时器，第二次触发开，第三次触发关
		if(TR0) { //定时器开时
			ex0_flag = 1;
		}
		if(!TR0) {        
			EX0 = 0;      
			cal_flag = 1; //计算标志置1，即可以计算两次下降沿的值			
			ex0_flag = 0;
		}
	} 
}

void Timer0_ISR() interrupt 1{
	count = count + 1;
	TL0 = 0;
	TH0 = 0;
}

void main() {
	unsigned int pData[4] = 0;
	unsigned int addr, frc;
	char buf[17];
	//unsigned long rotation;
	UART_Init();
	TM7705_Init();
	EX0_Init();
	//自校准
	TM7705_CalibSelf(1);
	TM7705_CalibSelf(2);
	while(1) {
		//while(cal_flag != 1);
		/*if (cal_flag == 1) {
			EX0 = 0;
			cal_flag = 0;
			//rotation = 65536 * count + 256 * TH0 + TL0;
			//printf("%d \r\n", count);
			//printf("%8.3f Hz \r\n", 1000000/(1.08*(65536 * count + 256 * TH0 + TL0)));
			pData[0] = count;
			pData[1] = 256 * TH0 + TL0;			
			pData[2] = TM7705_ReadAdc(1);
			pData[3] = TM7705_ReadAdc(2);
			MODBUS(pData, 3, 1); 
			count = 0;
			TH0 = 0;
			TL0 = 0;
			EX0 = 1;
		} */
		/*
		if(scanf("%s", Str)) {
			printf("Ture");
		}*/
		if(scanf ("%s", buf)) {
			if(buf[0] == ':') {
				if(sscanf(buf+1, "%2x%2x*", &addr, &frc)) {
					if(addr == ADDR) {
						MODBUS(pData, ADDR, frc);
					}
				}
			}
		}
	}
}