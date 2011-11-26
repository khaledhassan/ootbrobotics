/*
 * other.c
 *
 * Created: 11/12/2011 12:39:32 AM
 *  Author: bfc
 */ 

#include "other.h"

volatile uint8_t flagReg = 0;
uint16_t servoDataBuffer[24];

volatile uint8_t currentServo = 0;

void setMasks(void){
	uint8_t i ;//simple increment 

		for(i=0;i<8;i++){
			servo[i].masks.portDMask = 0xC0; 
			servo[i].masks.portBMask = 0x80>>i; 
		}		
		for(i=0;i<8;i++){
			servo[i+8].masks.portDMask = 0xA0; 
			servo[i+8].masks.portBMask = 0x80>>i;
		}		
		for(i=0;i<8;i++){
			servo[i+16].masks.portDMask = 0x60;
			servo[i+16].masks.portBMask = 0x80>>i;
		}		
}

void refresh(void){
	uint8_t i;
	for(i=0;i<24;i++)servo[i].TimerVal = servoDataBuffer[i];
	currentServo = 0;
}
  
void seedValues(void){
	uint8_t i;
	for(i=24;i>0;i--)servoDataBuffer[24-i] = (uint16_t)((i)*15 + 50);  
}	
 
void sort(void){
	uint8_t i,ErrorFound = 1;
	while(ErrorFound){
		ErrorFound = 0;
		for(i=1;i<24;i++){
			if(servo[i].TimerVal < servo[i-1].TimerVal){
				temp = servo[i];
				servo [i] = servo[i-1];
				servo[i-1] = temp;		
				ErrorFound = 1;	
			}				
		}
	}
}

void postSortMask(void){
	uint8_t i,temp[3];
	
	for(i=0;i<3;i++)temp[i] = 0;
	
	for(i=0;i<24;i++){
		switch(servo[i].masks.portDMask){
			case(0xC0):
				servo[i].masks.portBMask |= temp[0];
				temp[0] = servo[i].masks.portBMask;
			break;
			case(0xA0):
				servo[i].masks.portBMask |= temp[1];
				temp[1] = servo[i].masks.portBMask;
			break;
			case(0x60):
				servo[i].masks.portBMask |= temp[2];
				temp[2] = servo[i].masks.portBMask;
			break;
		}
	}
}

void seedTimerCompares(void){
	OCR1A = servo[currentServo].TimerVal;
//	OCR1B = servo[currentServo + 1].TimerVal;
}