/*
 	example-LED-Switch.c
 
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