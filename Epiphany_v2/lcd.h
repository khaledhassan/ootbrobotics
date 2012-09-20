/*
 * lcd.h
 *
 * Created: 7/2/2011 2:18:05 AM
 *  Author: Tim
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>


#define LCD_BUSY_FLAG	7


#define LCD_CLEAR			0x01
#define LCD_HOME			0x02
#define	LCD_ENTRYMODE		0x06
#define LCD_DISPLAYCTRL		0x0C
#define LCD_SHIFTCTRL		0x14
#define LCD_FUNCSET			0x28


#define LCD_ENABLE			1<<0	
#define LCD_RW				1<<1
#define LCD_RS				1<<2
#define LCD_DATA_PIN_msk	0xF0


void LCDInit(void);
void LCDSetCursor(uint8_t col, uint8_t row);


//private functions
void waitWhileLCDBusy(void);
void LCDCommand(uint8_t data);
void LCDWrite(uint8_t data);
void LCDEnableInterrupt(void);
void LCDDisableInterrupt(void);
void LCDStrobe(uint8_t read);
void outNibble(uint8_t nibble,uint8_t RS);

int lcd_putchar(char c, FILE *unused);

FILE lcd_str;


#endif /* LCD_H_ */