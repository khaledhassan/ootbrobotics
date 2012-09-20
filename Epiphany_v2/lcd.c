/*
 * lcd.c
 *
 * Created: 7/2/2011 2:18:17 AM
 *  Author: Tim
 */ 
#include "lcd.h"

FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

void LCDInit(void){
	PORTJ.OUTSET = LCD_RS | LCD_RW;
	PORTJ.DIRSET = LCD_ENABLE | LCD_RS | LCD_RW | LCD_DATA_PIN_msk;

	PORTJ.PIN4CTRL = 0x10;
	PORTJ.PIN5CTRL = 0x10;
	PORTJ.PIN6CTRL = 0x10;
	PORTJ.PIN7CTRL = 0x10;
	
	_delay_ms(10);
	PORTJ.OUTCLR = LCD_RS | LCD_RW;
	_delay_ms(50);	
	outNibble(0x30,0);

	_delay_ms(5);
	outNibble(0x30,0);
	
	_delay_ms(.2);
	outNibble(0x30,0);
	
	outNibble(0x20,0);
	waitWhileLCDBusy();
	LCDCommand(0x28);
	waitWhileLCDBusy();
	LCDCommand(0x0C);
	waitWhileLCDBusy();
	LCDCommand(0x01);
	waitWhileLCDBusy();
	LCDCommand(0x06);
}
void waitWhileLCDBusy(void){
	PORTJ.DIRCLR = LCD_DATA_PIN_msk;
	PORTJ.OUTCLR = 0xF0;
	PORTJ.OUTCLR = LCD_RS;
	PORTJ.OUTSET = LCD_RW;
	_delay_us(1);
	LCDStrobe(1);
	LCDStrobe(0);
	PORTJ.DIRSET = LCD_DATA_PIN_msk;
}
void LCDCommand(uint8_t data){
	outNibble(data,0);
	outNibble(data<<4,0);
}
void LCDWrite(uint8_t data){
	waitWhileLCDBusy();
	outNibble(data,1);
	outNibble(data<<4,1);
}
void LCDSetCursor(uint8_t col, uint8_t row){
	
}
void LCDEnableInterrupt(){
	
}
void LCDDisableInterrupt(){
	
}
void LCDStrobe(uint8_t read){
PORTJ.OUTSET = LCD_ENABLE;
_delay_us(3);
	if(read){
	while(PORTJ.IN & 0x80);
	}
PORTJ.OUTCLR = LCD_ENABLE;
_delay_us(3);
}

void outNibble(uint8_t nibble,uint8_t RS)
{
	PORTJ.OUTCLR = LCD_RW;
	
	if(RS)	PORTJ.OUTSET = LCD_RS;
	else	PORTJ.OUTCLR = LCD_RS;
	PORTJ.OUTCLR = 0xF0;
	PORTJ.OUTSET = nibble & 0xF0;
	LCDStrobe(0);
}

int lcd_putchar(char c, FILE *unused)
{
  static bool nl_seen,cr_seen;
  if(cr_seen && c != '\r'){
	  waitWhileLCDBusy();
	  LCDCommand(LCD_CLEAR);
      waitWhileLCDBusy();
	  LCDCommand(LCD_HOME);
      waitWhileLCDBusy();
//      hd44780_outcmd(HD44780_DDADDR(0));		 
	  cr_seen = false;
  } 
  else if(c == '\r'){
	cr_seen = true;
  }	 
  else if (nl_seen && c != '\n')
    {
	  /*
       * First character after newline, move cursor to next line.
       */
	  waitWhileLCDBusy();
	  LCDCommand(0x80 | 0x40);
	  //hd44780_outcmd(HD44780_DDADDR(0x40));
	 
	  nl_seen = false;
    }
  if (c == '\n')
    {
      nl_seen = true;
    }
  else
    {
      waitWhileLCDBusy();
	  
      LCDWrite(c);
    }

  return 0;
}
