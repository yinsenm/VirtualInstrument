/*
	LCD1602	头文件
*/

#include <reg52.h>
#include <intrins.h>

#ifndef __1602_H__
#define __1602_H__

bit LCD_Check_Busy();

void LCD_Write_Com(unsigned char com);

void LCD_Write_Data(unsigned char data);

void LCD_Clear();

void LCD_Init();

void LCD_Write_Str(unsigned char x, unsigned char y, unsigned char *str);
   
#endif
