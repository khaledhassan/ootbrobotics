/*
 * other.h
 *
 * Created: 11/12/2011 12:39:43 AM
 *  Author: bfc
 */ 


#ifndef OTHER_H_
#define OTHER_H_

#include <avr/io.h>

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
void postSortMask(void);

uint8_t *servoBusPtr;
uint16_t *servoTimePtr;

struct ServoData{
		
	struct ServoBus{
		uint8_t masks[3];
	}bus[24],tempBus;	
		
	struct ServoTimes{
		volatile uint16_t timerVal;
	}times[24],tempTimes;
		
}servos;

struct ServoBuffer{
	uint16_t timerVal;
}servoBuffer[24];


#define servoBusBegin &servos.bus[0].masks[0]
#define servoTimesBegin &servos.times[0].timerVal
#define servoTimesEnd &servos.times[23].timerVal

void mulitpleServoTimeFix();
//void getServoValues();
//void servoDataIRQ();

uint8_t		servoIdentifier;

union ServoTime{
	uint16_t	Val;
	struct Byte{
	uint8_t		_L;	//apparently the attiny is bigEndien
	uint8_t		_H;
	}byte;
}servoTime;
uint8_t		check;

uint8_t mainBus[3];

#endif /* OTHER_H_ */