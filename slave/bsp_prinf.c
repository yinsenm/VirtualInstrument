// 重定义 putchar 函数， 这样可以使用printf函数从串口打印输出
#include "uart.h"
char putchar(char c) {
	UART_SendByte(c);
	return c;
}

// 重定义C库中的 getchar 函数,这样可以使用scanff函数从串口输入数据

char _getkey() {
	return UART_GetByte();
}

/*char getchar(void) {
	return UART_GetByte();
}*/