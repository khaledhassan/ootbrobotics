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
#include "ATtinyServo.h"
#include "ADC.h"
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
	ATtinyServoInit();//this function initializes the servo controller on the Attiny
	uartInit(&USARTC0,115200);//as can be seen in the schematic.  This uart is connected to the USB port.  This function initializes this uart	
	uartInit(&USARTE1,9600);//as can be seen in the schematic.  This uart is connected to the Xbee port.  This function initializes this uart	
	ADCsInits();//this function initializes the ADCs inside the Xmega		 
	sei();
	
	uint16_t i,j;
		

		
	while (1)
	{
		
		//uncomment code based on what demo you want to run
		
		
		//adc example
		//this code reads in data from the 8 ADC channels on port A and spits them out the USB serial port
		//&USB_str specifies the usb port as the target device to print to
		//%d is used to sepcify print the next variable of type integer(decimal base)
		// /r and /n are carriage return and newline special characters
		//also you could easily make this into an Xbee port by simply changing &USB_str to &Xbee_str
		
		// analogRead_ADCA( uint8_t channel) is a simple function used ti get data from the ADC (analog to digital converter)
		
//demo	ADC code	
		/*
		for(i=0;i<8;i++){
		fprintf(&USB_str,"ADC channel %d = %d\r\n\r\n",i,analogRead_ADCA(i));
		}		
		_delay_ms(100);//delay 100 milliseconds
		*/	
		
		//motor control example
		/*
		this code simply turns all motors on and sweeps them up to full speed
		MOTOR_PERIOD_gc = 1024 and is the maximum value for duty cycle which is generally a percentage from 0-100
			however I broke that convention for more efficient coding.  So its a bit of a mis nomer....my bad
		MOTOR_DIR_FORWARD_gc sets the motors to turn in the forward direction which is also a little misleading since your wiring also effects the direction of motor spin
		*/
//demo motor code		
		/*
		for(i=1;i<5;i++){
			for(j=0;j<MOTOR_PERIOD_gc;j++) setMotorDuty(i,j,MOTOR_DIR_FORWARD_gc);
			_delay_ms(10);//delay 10 milliseconds
		}			
		*/
		
		//servo demo
		/*
		these code snippets will move servo 5 in a sweep.  Notice a delay of some type is required
		since the servos have a finite response time of > 20ms.  If you move the positions too fast
		the servos will merely jitter in place.  SO don't do that.
		
		There are two ways of controlling the servos angle and position. Angle is in degrees position
		is a number 1.5* the pulse width in us. Typical widths are 600-2400us so 900-3600
		
		Currently angle only "really" applies to hitech based servos since their timing is in agreement
		with this code.  However I plan to implement further logic to account for different servo timings in the future.
		Honestly though the difference is quite minimal from hitch to say Futaba.  So you probably won't
		even notice 
		*/
		
		
//servo angle set demo		
		/*
		for(i=0;i<180;i++){
			setServoAngle(5,i);
			_delay_ms(50);//delay 50 milliseconds
		}
		for(i=180;i>0;i--){
			setServoAngle(5,i);
			_delay_ms(50);//delay 50 milliseconds
		}
		*/		
//servo position set demo		
		/*		
		for(i=900;i<3600;i++){
			setServoPosition(5,i);
			_delay_ms(50);//delay 50 milliseconds
		}
		}
		for(i=3600;i>900;i--){
			setServoPosition(5,i);
			_delay_ms(50);//delay 50 milliseconds
		}
		*/
	}
						
}
