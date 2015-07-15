/*
	延时程序
*/

#include "delay.h"

/*
	Func: 延时 t * 2 + 5 uS
*/
void DelayUs2x(unsigned char t) {   
	while(--t);
}


/*
	Func: 大致延时1 ms
*/
void DelayMs(unsigned char t) {
	while(t--) {
		DelayUs2x(245);
		DelayUs2x(245);
	}
}
