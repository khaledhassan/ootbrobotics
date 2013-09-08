/*
 * example4.c
 *
 * Created: 8/29/2013 1:05:36 AM
 *  Author: Tim
 */ 

#include "Epiphany.h"

uint8_t usbData;
int8_t pNumber = 0;

void setup()
{
	//initialize system clock to 32MHz
	clockInit();
	
	//initialize the real time clock 
	RTC_DelayInit();
	
	//initialize the uart connected to the USB interface
	usbInit(115200);		
	
	//initialize the ADC
	adcInit();
	
	//global interrupt enable
	sei();
}

void loop()
{
	if(delayOver)
	{
		fprintf(&USB_str,"analog pin %d = %1.4f\r\n",pNumber,5*(analogRead(pNumber)+1)/4096.0);
		
		if(dataInBufUSB())
		{
			fscanf(&USB_str,"%c",&usbData);
			if		(usbData == 'i')
			{
				if (++pNumber > 7) pNumber = 0;
			}
			else if (usbData == 'o')
			{
				if (--pNumber < 0) pNumber = 7;
			}
		}
		
		RTC_Delay_ms(25);
	}
	
}