/*
   example-ADC.c
 
   To run this example
 
   1)	locate the solution explorer window, 
 		If it is not displayed, you can find 
 		it via "View/Solution Explorer" 
 		or Ctrl + Alt + L
   
   2)	Right click on your project file which 
 		has a default name of "renameMe.c".  
		Select properties form the window. 
		There will be an item labeled Build Action
		select none instead of compile
	
	3)	follow the same process as step 2 for 
		This file however instead of selection
		none, select compile. 
		
	***	Note when you are finished with the example 
		you should set it's build action to none, and
		set your project file back to compile 
		
 */ 

#include "../Epiphany.h"

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