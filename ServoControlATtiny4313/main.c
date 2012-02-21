 /*
 * ServoControlATtiny4313.c
 *
 * Created: 10/30/2011 1:36:20 AM
 *  Author: bfc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/wdt.h>
#include <stdbool.h>

#include "timer.h"
#include "uart.h"
#include "other.h"

#define newDataExists() (UCSRA & _BV(RXC))

void initializations(void);
void servoSignalLoop(void);
void processingForNextLoop(void);

uint8_t buffer[4];
bool servosEnabled = false;

int main(void)
{
	wdt_enable(WDTO_500MS);	
	servosEnabled = false;
	initializations();
	PORTD &= ~DBLED;
	while(1)
    {
		
		servoSignalLoop();			//sends all the servo signals 
		
		processingForNextLoop();	//processes the current servoBuffer Values
		
		servoDataIRQ();				//sends an interrupt request to the Xmega	
		
				
		while(TCNT1>500)
		{		
			testArray();
			if(newDataExists()){
				repopulateArray();
				servoDataIRQ();
			}
			
		}
		asm("nop");
    }
}



ISR(TIMER1_COMPA_vect){
	cli();
	if(servosEnabled){
		PORTB =	mainBus[0]; 
		PORTD +=DECODE0;	     
		PORTB =	mainBus[1]; 
		PORTD +=DECODE0;			
		PORTB =	mainBus[2];		
		PORTD +=DECODE1;		
		PORTD &= 0x0F;
	}
	else	PORTD ^=DBLED;
	sei();
}

void initializations(void){
	DDRB = 0xFF;//disable all port B pins (servo pins as Outputs) for the case of wdt resets
	DDRD = 0xFE;//enables every pin except the uart receive pin as an output
	PORTB = 0;
	PORTD |= DECODE0 | DECODE1 | DECODE2;
	PORTD &= 0x0F;
	uartInit();
	refresh();
	setMasks();
	seedValues();
	sort();
	postSortMask();
	mulitpleServoTimeFix();
	timer1Init();
	sei();
}

void servoSignalLoop(void){
	do 
		{
			if(TCNT1>(uint16_t)*servoTimePtr){		
				if((uint16_t)*servoTimePtr != 0 && servosEnabled){
					PORTB =	*servoBusPtr++; 
					PORTD +=DECODE0;	     
					PORTB =	*servoBusPtr++; 
					PORTD +=DECODE0;			
					PORTB =	*servoBusPtr++;		
					PORTD +=DECODE1;		
					PORTD &= 0x0F;
					servoTimePtr++;
				}				
				else{
					servoBusPtr += 3;
					servoTimePtr++;
				}
			}					
		} while (servoTimePtr <= servoTimesEnd); 
}

void processingForNextLoop(void)
{
	
	refresh();
	
	//this makes sure the message timeout acctually works
	buffer[0]=0x0;
	buffer[1]=0x0;
	buffer[2]=0x0;
	buffer[3]=0x0;
	
	setMasks();
	sort();
	postSortMask();
	
	mulitpleServoTimeFix();
}


inline testArray(void){
	if(buffer[0] < 50 ){
		if(buffer[3] == (0x80 | buffer[0]) )
		{
			servoBuffer[buffer[0]].timerVal = (buffer[1])<<8 | buffer[2] ;	
				wdt_reset();
				PORTD |= DBLED;
				servosEnabled = true;
		}
	}
}

inline repopulateArray(void){
	uint8_t i;
	for(i=0;i<3;i++) buffer[i] = buffer[i+1];
	buffer[3] = UDR;
}

ISR(BADISR_vect){
	asm("nop");
}