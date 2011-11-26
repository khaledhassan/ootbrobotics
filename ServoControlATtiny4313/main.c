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

#include "global.h"
#include "timer.h"
#include "uart.h"
#include "other.h"



uint8_t uartGetC(void);


int main(void)
{
	
	DDRB = 0xFF;//enable all port B pins (servo pins as Outputs)
	DDRD = 0xFE;//enables every pin except the uart receive pin as an output
	PORTD |= 0x4;
	uartInit();
	setMasks();
	seedValues();
	refresh();
	sort();
	seedTimerCompares();
	timer1Init();
	sei();
	while(1)
    {
		while(currentServo<24);
		setMasks();
		seedValues();
		refresh();
		sort();
		seedTimerCompares();	
		asm("nop");
	
    }
}



ISR(BADISR_vect){}

ISR(USART_RX_vect){
	//uartGetC(); set this equal to the current buffer location	
}

ISR(TIMER1_COMPA_vect){
	OCR1A = servo[currentServo + 1].TimerVal;	
	PORTD = _BV(DECODE0) | _BV(DECODE1) | _BV(DECODE2);
	PORTB = servo[currentServo].masks.portBMask;
	PORTD = servo[currentServo++].masks.portDMask;
}

uint8_t uartGetC(){
	return UDR;
}


