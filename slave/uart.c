/*
	串口驱动模块
*/

#include <reg52.h>

static char echo_flag = 0;

// 串口中断
void UART_isr() interrupt 4 {
	if (RI) {

	}
}

//串口初始化
void UART_Init() {	    //9600bps@11.0592MHz
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	TI = 1;
}

//复写 putchar
char putchar(char c) {
	if(!echo_flag) {
		if (c == '\n') {
			while (!TI);
    		TI = 0;
    		SBUF = 0x0D;   /* output CR  */
  		}
  		while (!TI);
  		TI = 0;
  		SBUF = c;
	}
	echo_flag = 0;
	return c;
}

//复写 _getkey()
char _getkey() {
	char c;
  	while (!RI);
  	c = SBUF;
  	RI = 0;
  	echo_flag = 1;
  	return c;
}
