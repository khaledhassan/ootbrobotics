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

#include "timer.h"
#include "uart.h"
#include "other.h"



uint8_t uartGetC(void);


int main(void)
{
	
	DDRB = 0xFF;//enable all port B pins (servo pins as Outputs)
	DDRD = 0xFE;//enables every pin except the uart receive pin as an output
	PORTD = 0;
	uartInit();
	refresh();
	setMasks();
	seedValues();
	sort();
	postSortMask();
	timer1Init();
	sei();
	while(1)
    {
		
		do 
		{
			if(TCNT1>(uint16_t)*servoTimePtr){
				
				PORTB =		*servoBusPtr++; //set the bus
				PORTD =	    DECODE0;	    //turn on the decode0 strobe 
				PORTD &=	0xF;
				
				PORTB =		*servoBusPtr++; //set the bus
				PORTD =		DECODE1;		//turn on the decode1 strobe	
				PORTD &=	0xF;
				
				PORTB =		*servoBusPtr++;	//turn on the decode2 strobe
				asm("nop");
				asm("nop");
				asm("nop");
				
				PORTD =		DECODE2;		//set the bus		
				PORTD &=	0xF;	
				servoTimePtr++;		
			}					
		} while (servoTimePtr < servoTimesEnd);
		refresh();
		setMasks();
		seedValues();
		sort();
		postSortMask();
		while(TCNT1>0);
    }
}



ISR(BADISR_vect){}

ISR(USART_RX_vect){
	uartGetC(); //set this equal to the current buffer location	
}

inline ISR(TIMER1_COMPA_vect){
		PORTD =	    DECODE0 | DECODE1 | DECODE2;
		PORTB =		0xFF;
		PORTD =	    0;
}

uint8_t uartGetC(){
	return UDR;
}


