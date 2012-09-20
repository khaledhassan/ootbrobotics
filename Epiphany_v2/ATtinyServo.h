/*
 * ATtinyServo.h
 *
 * Created: 11/13/2011 3:16:55 PM
 *  Author: bfc
 */ 


#ifndef ATTINYSERVO_H_
#define ATTINYSERVO_H_ ,

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>

enum SERVO_TYPE{
	SERVO_SERVOTYPE_HITEC_bm = 0,
	SERVO_SERVOTYPE_FUTABA_bm = 1	
};

struct Servo{
	uint16_t	servoTime;
	union ConFigReg{
		uint8_t		statusReg;
		struct	{
			uint8_t idleCycles	:	5;	//counts idle cycles (20ms) up to 25 or so which corresponds to a 2Hz refresh rate
									//this allows for low maintenance on idle servos  	
			bool servoType	:	1;			// 1 = Futaba, 0 = Hitech 
			bool upToDate	:	1;			// 1 = servo value is current, 0 = servo value is old
			bool enabled	:	1;			// 1 = servo is enabled, 0 servo is disabled
						
		}params;
	}configReg;		
}servo[24];



void ATtinyServoInit(void);
void servo_putchar(char c,FILE *unused);
int servo_getchar(FILE *stream);
void storeServo(char c);
uint8_t dataInServoBuffer(void);
void disableServo(uint8_t servoNumber);
void setServoAngle(uint8_t servoNumber,uint8_t angle);
void setServoPosition(uint8_t servoNumber, uint16_t servoPosition);
uint8_t getServoAngle(uint8_t servoNumber);
uint16_t getServoPosition(uint8_t servoNumber);



FILE	servoBufferFile; /*	printf will poplulate a servo buffer in memory.  
						Scanf will feed the uart for servo control.
						This will be triggered upon a PCINT coincidently
						on the RX pin of the servo Uart.*/

#endif /* ATTINYSERVO_H_*/ 