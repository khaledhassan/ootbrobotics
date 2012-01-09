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



int main(void)
{
//	wdt_enable(WDTO_1S);
	bytesInBuffer = 0;
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
	while(1)
    {
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
		} while (servoTimePtr <= servoTimesEnd); //servoTimePtr <= servoTimesEnd &&
		refresh();
		setMasks();
		sort();
		postSortMask();
		mulitpleServoTimeFix();
		UCSRB |=  _BV(RXCIE);	//enable the recieve interrupt on the uart	
		servoDataIRQ();	//sends an interrupt request to the Xmega	
				
		
		while(TCNT1>200)
		{
		/*	if(bytesInBuffer >= 4){
				servoIdentifier = uart_getchar(NULL);
				if(servoIdentifier <= 23){
					servoTime.byte._H = uart_getchar(NULL);
					servoTime.byte._L = uart_getchar(NULL);
					check = uart_getchar(NULL);
					if(check == (servoIdentifier | 0x80) ){
						servoBuffer[servoIdentifier].timerVal = servoTime.Val;
					}
					else flush(); //this kills stuff				
				}					
			}*/
		}
		asm("nop");
    }
}

ISR(BADISR_vect){
	asm("nop");
}

ISR(TIMER1_COMPA_vect){
	cli();
	PORTB =	0xFF;//mainBus[0]; 
	PORTD +=DECODE0;	     
	PORTB =	0xFF;//mainBus[1]; 
	PORTD +=DECODE0;			
	PORTB =	0xFF;//mainBus[2];		
	PORTD +=DECODE1;		
	PORTD &= 0x0F;
	UCSRB &=  ~_BV(RXCIE);//disable RX interrupt so there are no interruptions to the time critical servo code.
	sei();
}


