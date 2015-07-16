#include "delay.h"
#include "tm7705.h"
// #include "i2c.h"
// #include "1602.h"
#include "uart.h"
#include <stdio.h>
#include <reg52.h>

void main() {
	unsigned int adc1, adc2;
	UART_Init();
	TM7705_Init();
	//自校准
	TM7705_CalibSelf(1);
	TM7705_CalibSelf(2);
	while(1){
		adc1 = TM7705_ReadAdc(1);
		adc2 = TM7705_ReadAdc(2);
		printf("CH1 = %04X, (%7.5f) V \t CH2 = %04X, (%7.5f) V \r\n", adc1, (adc1*5.0)/65535, adc2, (adc2*5.0)/65535);
	}
}