/*
	I2C 协议
*/
#include "i2c.h"
#include "delay.h"

bit ack; //应答位

sbit SDA = P2^1;
sbit SCL = P2^0;

/*
	启动总线
*/
void Start_I2C() {
	SDA = 1;
	_nop_();
	SCL = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SDA = 0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCL = 0;
	_nop_();
	_nop_();
}

/*
	结束总线
*/
void Stop_I2C() {
	SDA = 0;
	_nop_();
	SCL = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SDA = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

/*
	传送一个字节数据
	将数据c发送出去, 可以是地址, 也可以是数据,
	发完后等待应答, 并返回此状态位.
*/
bit SendByte(unsigned char c) {
	unsigned char BitCnt;
	for(BitCnt = 0; BitCnt < 8; BitCnt++){
		if((c<<BitCnt) & 0x80)
			SDA = 1;
		else
			SDA = 0;
		_nop_();
		SCL = 1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		SCL = 0;
	}
	//准备接受应答位
	_nop_();
	_nop_();
	SDA = 1;
	_nop_();
	_nop_();
	SCL = 1;
	_nop_();
	_nop_();
	_nop_();
	if (SDA == 1)
		ack = 0;
	else
		ack = 1;
	SCL = 0;
	_nop_();
	return (bit)(ack);
}

/*
	接受一个字节数据
	不应答，发送一系列数据后用应答函数
*/
unsigned char RcvByte(){
	unsigned char retc = 0;
	unsigned char BitCnt;

	SDA = 1;
	for (BitCnt = 0; BitCnt < 8; BitCnt ++){
		_nop_();
		SCL = 0;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		SCL = 1;
		_nop_();
		_nop_();
		retc = retc + 1;
		if(SDA)
			retc += 1
		_nop_();
		_nop_();
	}
	SCL = 0;
	_nop_();
	_nop_();
	return retc;
}

/*
	应答函数
*/
void Ack_I2C(){
	SDA = 0;
	_nop_();
	_nop_();
	_nop_();
	SCL = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCL = 0;
	_nop_();
	_nop_();
}

/*
	不应答函数
*/
void No_Ack_I2C(){
	SDA = 1;
	_nop_();
	_nop_();
	_nop_();
	SCL = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCL = 0;
	_nop_();
	_nop_();
}

