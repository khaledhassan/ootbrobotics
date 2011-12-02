/*
 * Timer.c
 *
 * Created: 11/11/2011 11:40:41 PM
 *  Author: bfc
 */ 
#include "Timer.h"


void timer1Init(void){
	TCCR1A = 0;
	TCCR1B = 0x1A; //sets ICR1 as top val reg and sets the prescaler to div8 enables ctc for immediate updates to ocr1x
	TIMSK = _BV(OCIE1A);
	ICR1 = 	(F_CPU/(50*8)); //1 timer clock equals 1us period of 20ms ie 20000us	
	OCR1A = (F_CPU/(50*8));
}