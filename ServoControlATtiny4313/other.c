/*
 * other.c
 *
 * Created: 11/12/2011 12:39:32 AM
 *  Author: bfc
 */ 

#include "other.h"

void setMasks(void){
	uint8_t i;//simple increment 
		for(i=0;i<8;i++){
			servos.bus[i].masks[0] = ~(0x80>>i);
			servos.bus[i].masks[1] = 0xFF;
			servos.bus[i].masks[2] = 0xFF;
		}
					
		for(i=0;i<8;i++){
			servos.bus[i+8].masks[0] = 0xFF;
			servos.bus[i+8].masks[1] = ~(0x80>>i);
			servos.bus[i+8].masks[2] = 0xFF;
			
		}
		
		for(i=0;i<8;i++){
			servos.bus[i+16].masks[0] = 0xFF;
			servos.bus[i+16].masks[1] = 0xFF;
			servos.bus[i+16].masks[2] = ~(0x80>>i);
		}
}

void refresh(void){
	uint8_t i;
	//refresh all the servos
	for(i=0;i<24;i++)servos.times[i].timerVal = servoBuffer[i].timerVal;
	currentServo = 0;
	
	//initialize all the pointers
	servoBusPtr = &servos.bus[0].masks[0];
	servoTimePtr = &servos.times[0].timerVal;
	servoBufferPtr = &servoBuffer[0].timerVal;
}
  
void seedValues(void){
	uint8_t i;
	for(i=0;i<24;i++)servos.times[i].timerVal = (uint16_t)((23-i)*15 + 900);  
}	
 
void sort(void){
	uint8_t i,ErrorFound = 1;
	while(ErrorFound){
		ErrorFound = 0;
		for(i=1;i<24;i++){
			if(servos.times[i].timerVal < servos.times[i-1].timerVal){
				servos.tempBus = servos.bus[i];
				servos.tempTimes = servos.times[i];
				
				servos.times[i] = servos.times[i-1];
				servos.bus[i] = servos.bus[i-1];
			
				servos.times[i-1] = servos.tempTimes;
				servos.bus[i-1] = servos.tempBus;
			
				ErrorFound = 1;	
			}				
		}
	}
}

void postSortMask(void){
	uint8_t i,j;
	for(i=0;i<23;i++){
		for(j=0;j<3;j++)servos.bus[i+1].masks[j] &= servos.bus[i].masks[j];
	}
}

void seedTimerCompares(void){
	OCR1A = (uint16_t)*servoTimePtr++;
}