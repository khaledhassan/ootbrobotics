/*
 * ATtinyServo.h
 *
 * Created: 11/13/2011 3:16:55 PM
 *  Author: bfc
 */ 


#ifndef ATTINYSERVO_H_
#define ATTINYSERVO_H_

#include <avr/io.h>
#include "uart.h"

enum SERVO_TYPE{
	Hitech,
	FUTABA	
};

struct SERVO{
	uint8_t				servoNumber;
	volatile uint16_t	timerVal;
	volatile uint8_t	checksum;
}servo[24];

struct SERVO_PARAMS{
	PROGMEM uint16_t offsetL;
	PROGMEM uint16_t offsetH;
}servoParam[24];

void ATtinyServoInit(void);
void DMAEnable(void);
void DMADisable(void);
void USARTE0DMASetup(void);
void setServoTime(uint8_t servoNumber,uint16_t servoTime);
uint8_t getServoAngle(uint8_t servoNumber, enum SERVO_TYPE servoType);
uint16_t getServoTime(uint8_t servoNumber);




#endif /* ATTINYSERVO_H_ */