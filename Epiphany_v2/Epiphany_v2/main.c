/*
 * Epiphany_v2.c
 *
 * Created: 7/16/2012 10:50:18 PM
 *  Author: Tim
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#include "clock.h"
#include "ATtinyServo.h"
#include "uart.h"
#include "adc.h"


int main(void)
{
	clockInit();
	adcInit(&ADCA);
	ATtinyServoInit();
	usartInit(&USARTC0,115200);
	PORTC.DIRSET =0x08; 
	sei();
	uint8_t i,j;
	while(1)
    {	

					
	}



}
