/*
	LCD1602	
*/

#include "1602.h"
#include "delay.h"

//define 
sbit RS = P2^4;
sbit RW = P2^5;
sbit EN = P2^6;

#define DataPort P0

/*
	Func: 判断LCD是否忙
*/
bit LCD_Check_Busy(){
	DataPort = 0xFF;
	RS = 0;
	RW = 1;
	EN = 0;
	_nop_();
	EN = 1;
	return (bit)(DataPort & 0x80);
}

/*
	Func: 写入命令
*/
void LCD_Write_Com(unsigned char com){
	while(LCD_Check_Busy());
	RS = 0;
	RW = 0;
	EN = 1;
	DataPort = com;
	_nop_();
	EN = 0;
}

/*
	Func: 写入数据
*/
void LCD_Write_Data(unsigned char data){
	while(LCD_Check_Busy());
	RS = 1;
	RW = 0;
	EN = 1;
	DataPort = data;
	_nop_();
	EN = 0;
}

/*
	Func: 清屏
*/
void LCD_Clear(){
	LCD_Write_Com(0x01);
	DelayMs(5);
}

/*
	Func: 初始化LCD
*/
void LCD_Init() {
	LCD_Write_Com(0x38);
	DelayMs(5);
	LCD_Write_Com(0x38);
	DelayMs(5);

	LCD_Write_Com(0x38); //2行 8位传送 5*7 点阵 #6
	LCD_Write_Com(0x08); //关闭LCD  #4
	LCD_Write_Com(0x01); //清屏
	LCD_Write_Com(0x06); //输入设置 #3 画面不动 AC自动加一
	DelayMs(5);
	LCD_Write_Com(0x0C); //开光标   #4 光标开 闪烁关
}

/*
	Func: 写入字符串
*/
void LCD_Write_Str(unsigned char x, unsigned char y, unsigned char *str){
	if(y == 0){
		LCD_Write_Com(0x80 + x);
	}
	else{
		LCD_Write_Com(0xC0 + x);
	}
	while(*s){
		LCD_Write_Data(*s);
		s++;
	}
}


