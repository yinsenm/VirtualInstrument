/*
	喇叭头文件
*/
#ifndef __SPEAKER_H__
#define __SPEAKER_H__

#include <reg52.h>
#include "delay.h"

sbit SPK = P2^0;

void speaker(unsigned int num) {
	unsigned char i;
	while(num--) {
		for(i = 0; i < 200; i++) {
			DelayUs2x(200);
			SPK = !SPK;
		}
		SPK = 0;
		for(i = 0; i < 200; i++) {
			DelayMs(1);
		}
	}
}

#endif