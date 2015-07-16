/*
	串口驱动模块
*/

// 串口中断
void UART_isr() interrupt 4 {
	if (RI) {

	}
}

//串口发送一字节
void UART_SendByte(unsigned char _data) {
	SBUF = _data;	/* 发送数据送缓冲 */
	while(!TI);		/* 等待发送完成 */
	TI = 0;
}


//串口接收一字节
unsigned char UART_GetByte() {
	unsigned char c;
	while (RI == 0);
	c = SBUF;
	RI = 0;	
	return c;
}

//串口发送字符串
void UART_SendStr(unsigned char *str, unsigned char len) {
	while(len --){
		UART_SendByte(*str++);
	}
}

//串口初始化
void UART_Init() {	    //9600bps@11.0592MHz
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}
