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
#include "motor.h"


int main(void)
{
	clockInit();
	adcInit(&ADCA);
	ATtinyServoInit();
	usartInit(&USARTC0,115200);
	sei();
	while(1)
    {	
	
	}



}
