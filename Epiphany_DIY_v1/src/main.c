/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * AVR Software Framework (ASF).
 */





#include <asf.h>
#include <avr/io.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include "motor.h"
#include "lcd.h"
#include "uart.h"
#include "RTC.h"
//#include "picServo.h"
#include "ATtinyServo.h"
#include "ADC.h"
//#include "adcInt.h"
#include "sonar.h"

#define DbLedOn()		(PORTR.OUTCLR = 0x02)		//Turns the debug led on.  The led is connected with inverted logic
#define DbLedOff()		(PORTR.OUTSET = 0x02)		//Turns the debug led off.  The led is connected with inverted logic
#define DbLedToggle()	(PORTR.OUTTGL = 0x02)		//Toggles the debug led off.  The led is connected with inverted logic
	
int main (void)
{	
	board_init();	/*This function originates in the file init.c, and is used to initialize the Epiphany DIY
					  motorInit() is declared within because by default you the user should define what your
					  motor setup is to prevent hurting the Epiphany.  You can do this by 
					*/	  
	RTC_DelayInit();//initializes the Real time clock this seems to actually take an appreciable amount of time
	DbLedOn();	//I like to do this by default to show the board is no longer suspended in the bootloader.
	ATtinyServoInit();
	uartInit(&USARTC0,115200);//as can be seen in the schematic.  This uart is connected to the USB port.  This function initializes this uart	
	uartInit(&USARTE1,9600);//as can be seen in the schematic.  This uart is connected to the USB port.  This function initializes this uart	
	ADCsInits();//this function initializes the ADCs inside the Xmega		 
	sei();
//	fprintf_P(&USB_str,PSTR("Out of the Box:\rElectronics and Robotics\rPresents the\rEpiphany DIY\rSoftware Version %s\r%s"),sVersion,date);		
	asm("nop");
	uint16_t i,j;
	
	while (1)
	{
		for(i=900;i<3600;i+=8){
			for(j=1;j<25;j++)setServoPosition(20,i);
			_delay_ms(20);
		}

		for(i=3600;i>900;i-=8){
			for(j=1;j<25;j++)setServoPosition(20,i);
			_delay_ms(20);
		}
		
	}			
}
