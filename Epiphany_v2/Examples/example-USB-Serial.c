/*
 	example-USB-Serial.c
 
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