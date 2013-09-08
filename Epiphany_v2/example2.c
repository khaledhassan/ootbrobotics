/*
 * example2.c
 *
 * Created: 8/29/2013 1:05:36 AM
 *  Author: Tim
 */ 

#include "Epiphany.h"

void setup()
{
	dbledInit();
	
	//enable the pull-up resistor for the switch i/o pin
	PORTD.PIN0CTRL |= PORT_OPC_PULLUP_gc; 
	
	//the direction of all i/o pins default to inputs
	//therefore this is not a needed declaration if 
	//the pin is only used as an input
	PORTD.DIRCLR = 0x01;
}

void loop()
{
	//this code assumes the switch is NO (normally open)
	//once the switch is flipped the led will turn on.
	//if the switch is NC (normally closed) the led
	//will turn off when the switch is flipped
	
	//the switch should be wired as follows
	//one terminal connected to the i/o pin
	//one terminal connected to gnd
	 
	if(PORTD.IN & 0x01) dbledOff();
	else				dbledOn();
}