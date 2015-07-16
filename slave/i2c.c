/*
	I2C 协议
*/
#include "i2c.h"
#include "delay.h"

//bit ack; //应答位

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
	bit ack = 0;
	for (BitCnt = 0; BitCnt < 8; BitCnt++){
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
unsigned char RcvByte() {
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
		retc <<= 1;
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
void Ack_I2C() {
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
void No_Ack_I2C() {
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

/*
	向有子地址器件发送多字节数据函数
	sla,   slave address
	suba,  slave sub address
	*s,    pointer to a string to be sended
	num,   number of bytes to send 

*/
bit ISendStr(unsigned char sla,unsigned char suba, unsigned char *s, unsigned char num) {
	unsigned char i;
	for (i=0; i<num; i++) { 
		Start_I2c();           //启动总线
		if !SendByte(sla)      //发送器件地址
			return 0;
	   	if !SendByte(suba)     //发送器件子地址
	   		return 0;
	    if !SendByte(*s)       //发送数据
	    	return 0;
	    Stop_I2c();            //结束总线
		DelayMs(1);            //必须延时等待芯片内部自动处理数据完毕
		s++;
		suba++;
    } 
    return 1;
}

/*
	向有子地址器件接收多字节数据函数
	sla,   slave address
	suba,  slave sub address
	*s,    pointer to a string to be sended
	num,   number of bytes to send 

*/
bit IRcvStr(unsigned char sla, unsigned char suba, unsigned char *s, unsigned char num) {
	unsigned char i;
   	Start_I2c();                  //启动总线
   	if !SendByte(sla)             //发送器件地址
   		return 0;
   	if !SendByte(suba)            //发送器件子地址
   		return 0;
	//Start_I2c();
	if !SendByte(sla+1)
		return 0;
  	for(i=0; i<num-1; i++) { 
  		*s = RcvByte();              //发送数据
  		Ack_I2c();                 //发送就答位 
  		s++;
    } 
   	*s=RcvByte();
    NoAck_I2c();                   //发送非应位
    Stop_I2c();                    //结束总线
  	return 1;
}
