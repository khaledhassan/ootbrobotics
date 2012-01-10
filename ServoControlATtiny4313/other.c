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
			servos.bus[i].masks[0] = ~(1<<i);
			servos.bus[i].masks[1] = 0xFF;
			servos.bus[i].masks[2] = 0xFF;
		}
					
		for(i=0;i<8;i++){
			servos.bus[i+8].masks[0] = 0xFF;
			servos.bus[i+8].masks[1] = ~(1<<i);
			servos.bus[i+8].masks[2] = 0xFF;
			
		}
		
		for(i=0;i<8;i++){
			servos.bus[i+16].masks[0] = 0xFF;
			servos.bus[i+16].masks[1] = 0xFF;
			servos.bus[i+16].masks[2] = ~(1<<i);
		}
		servos.tempBus.masks[0] = 0x0;
		servos.tempBus.masks[1] = 0x0;
		servos.tempBus.masks[2] = 0x0;
		
		mainBus[0] = 0xFF;
		mainBus[1] = 0xFF;
		mainBus[2] = 0xFF;
		
		for(i=0;i<24;i++){ 
			if(servos.times[i].timerVal == 0 ) {
				servos.bus[i] = servos.tempBus;
				mainBus[i/8] &= (uint8_t)~(1<<i%8);
			}
			asm("nop");				
		}	
			
}

void refresh(void){
	uint8_t i;
	//refresh all the servos
	for(i=0;i<24;i++)servos.times[i].timerVal = servoBuffer[i].timerVal;
	
	//initialize all the pointers
	servoBusPtr = &servos.bus[0].masks[0];
	servoTimePtr = &servos.times[0].timerVal;
}
  
void seedValues(void){
	uint8_t i;
	for(i=0;i<24;i++)servos.times[i].timerVal = 0;  //normally 0
	
	for(i=0;i<24;i+=2)servoBuffer[i].timerVal = 2400*1.5;  //normally 0	
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
		for(j=0;j<3;j++){
			servos.bus[i+1].masks[j] &= servos.bus[i].masks[j];
			//servos.bus[i+1].masks[j] &= mainBus[j];
		}			
	}
}



//This function serves to decrease the 'unique' number of servos if there are multiple servos set to the same angle.
void mulitpleServoTimeFix(){
static uint8_t i;
	servos.tempBus = servos.bus[23];
	for(i=23;i>0;i--){
		if(servos.times[i-1].timerVal == servos.times[i].timerVal){ //if the current servo[i] is equal to the next servo down
			servos.times[i].timerVal = 0;							//the current servo time goes to 0
			servos.bus[i-1] = servos.bus[i];						//the next servo then takes the bus value of the next highest servo
		}			
	}
}	


void servoDataIRQ()
{
//if(bytesInBuffer < (bufferSize -2)) 
PORTD ^= 0x02;//this will trigger a PCINT on the xmega
}