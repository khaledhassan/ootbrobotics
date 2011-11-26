/*
 * other.h
 *
 * Created: 11/12/2011 12:39:43 AM
 *  Author: bfc
 */ 


#ifndef OTHER_H_
#define OTHER_H_

#include <avr/io.h>
#include "global.h"


enum PORTD_FUNCTIONS
	{
		 DECODE2		= 0x40,
		 DECODE1		= 0x20,
		 DECODE0		= 0x10,
		 RegOnOffCtrl	= 0x08,
		 DBLED			= 0x04
	};

enum FlagRegEnums{
		uartBufferOverflow	= 0x01,
		uartBufferNotEmpty	= 0x02,
		servoSignalsSent	= 0x04	
};

void setMasks(void);
void refresh(void);
void seedValues(void);
void sort(void);
void seedTimerCompares(void);

struct SortedServoData{
	uint16_t	TimerVal;	//the number used for determining the servos position
	//mask of this specific servo
	struct PORTMASKS 
	{
		uint8_t		portDMask;
		uint8_t		portBMask;
	}masks;
	
}servo[24],temp;

uint16_t servoDataBuffer[24];

volatile uint8_t currentServo;

#endif /* OTHER_H_ */