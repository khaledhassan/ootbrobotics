/*
 	example-Blink.c
 
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

void setup()
{
	//initialize the system clock to 32MHz
	//this is actually unnecessary since the RTC is system clock independent
	clockInit();
	
	//initialize the real time clock used for delays
	RTC_DelayInit();
	
	//initialize the uart used for the usb serial port
	usbInit(115200);
	
	//initialize the led pin for output
	dbledInit();
}

void loop()
{
	if(delayOver)
	{
		dbledTgl();
		RTC_Delay_ms(25);
	}
	
	/*
	code can run here while the RTC delay is counted up.
	using delays such as those in util/delay.h just waste
	clock cycles, that could be used for processing.  The
	RTC delay method used here is a great way to multi-task
	code in the MCU
	*/
	
}