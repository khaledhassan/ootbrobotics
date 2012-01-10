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

#include "timer.h"
#include "uart.h"
#include "other.h"

#define newDataExists() (UCSRA & _BV(RXC))

void initializations(void);
void servoSignalLoop(void);
void processingForNextLoop(void);

uint8_t buffer[4];

int main(void)
{

	initializations();
	while(1)
    {
		
		servoSignalLoop();			//sends all the servo signals 
		
		processingForNextLoop();	//processes the current servoBuffer Values
		
		servoDataIRQ();				//sends an interrupt request to the Xmega	
		
				
		while(TCNT1>600)
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

ISR(BADISR_vect){
	asm("nop");
}

ISR(TIMER1_COMPA_vect){
	cli();
	PORTB =	mainBus[0]; 
	PORTD +=DECODE0;	     
	PORTB =	mainBus[1]; 
	PORTD +=DECODE0;			
	PORTB =	mainBus[2];		
	PORTD +=DECODE1;		
	PORTD &= 0x0F;
//	UCSRB &=  ~_BV(RXCIE);//disable RX interrupt so there are no interruptions to the time critical servo code.
	sei();
}

void initializations(void){
//	bytesInBuffer = 0;
	DDRB = 0xFF;//enable all port B pins (servo pins as Outputs)
	DDRD = 0xFE;//enables every pin except the uart receive pin as an output
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
				if((uint16_t)*servoTimePtr != 0){
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
		}
	}
}

inline repopulateArray(void){
	uint8_t i;
	for(i=0;i<3;i++) buffer[i] = buffer[i+1];
	buffer[3] = UDR;
}