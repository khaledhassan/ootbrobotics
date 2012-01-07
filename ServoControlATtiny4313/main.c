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

#include "timer.h"
#include "uart.h"
#include "other.h"

static uint16_t angle = 900;


int main(void)
{
	bytesInBuffer = 0;
	DDRB = 0xFF;//enable all port B pins (servo pins as Outputs)
	DDRD = 0xFE;//enables every pin except the uart receive pin as an output
	PORTD = 0;
	uartInit();
	refresh();
	setMasks();
	seedValues();
	sort();
	postSortMask();
	mulitpleServoTimeFix();
	timer1Init();
	sei();
	while(1)
    {
		do 
		{
			if(TCNT1>(uint16_t)*servoTimePtr){		
				if((uint16_t)*servoTimePtr != 0){
					PORTB =	*servoBusPtr++; 
					PORTD =	DECODE0;	     
					PORTB =	*servoBusPtr++; 
					PORTD +=DECODE0;			
					PORTB =	*servoBusPtr++;		
					PORTD +=DECODE1;		
					PORTD =	0;
					servoTimePtr++;
				}				
				else{
					servoBusPtr += 3;
					servoTimePtr++;
				}
			}					
		} while (servoTimePtr <= servoTimesEnd);
		refresh();
		setMasks();
		sort();
		postSortMask();
		mulitpleServoTimeFix();
//		servoDataIRQ();
		
		
		bytesInBuffer = 0;
		uint8_t i;
		for(i=12;i<24;i++){
			uart_store(i);
			uart_store((angle & 0xFF00)>>8);
			uart_store((uint8_t)angle);
			uart_store(i | 0x80);
		}
		angle+=200;
		if(angle > 3600) angle = 900;
		while(TCNT1>10)
		{
				
			if(bytesInBuffer >= 4){
				servoIdentifier = uart_getchar(NULL);
				if(servoIdentifier <= 23){
					servoTime.byte._H = uart_getchar(NULL);
					servoTime.byte._L = uart_getchar(NULL);
					check = uart_getchar(NULL);
					if(check == (servoIdentifier | 0x80) ){
						servoBuffer[servoIdentifier].timerVal = servoTime.Val;
					}
					else flush();
				}					
			}
			else asm("nop");
	
		}
    }
}

ISR(BADISR_vect){}

ISR(TIMER1_COMPA_vect){
	PORTB =	mainBus[0]; 
	PORTD =	DECODE0;	     
	PORTB =	mainBus[1]; 
	PORTD +=DECODE0;			
	PORTB =	mainBus[2];		
	PORTD +=DECODE1;		
	PORTD =	0;
}


