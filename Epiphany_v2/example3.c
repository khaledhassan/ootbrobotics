/*
 * example3.c
 *
 * Created: 8/29/2013 1:05:36 AM
 *  Author: Tim
 */ 

#include "Epiphany.h"

uint8_t usbData;

void setup()
{
	//initialize system clock to 32MHz
	clockInit();
	
	//initialize the uart connected to the USB interface
	usbInit(115200);		
}

void loop()
{
	
	if(dataInBufUSB())
	{
		//read in a character from the USB buffer
		fscanf(&USB_str,"%c",&usbData);
		
		//print out the received character to the screen
		fprintf(&USB_str,"%c",usbData);
	}
}