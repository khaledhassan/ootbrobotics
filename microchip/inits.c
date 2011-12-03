#include "inits.h"
void initializations(){
	OSCCON = 0xF0;					//configures the internal oscilator to 32MHz
    APFCON0 = 0x84; 				//configures rx and tx for the appropriate pins
	TRISA = RX | SERVO_V | VIN_V;	//enables the correct pins on porta pins for output
	TRISC = SERVO_REG_T;			//enables the correct pins on portc pins for output
	
    //initializations
	uartInit();						//sets up uart
	spiInit();						//sets up the spi module
    timerInit();					//enables timer1 for servo timing 

	sei(); 							//enable global interrupts
    perIntEnable(); 				//enable peripheral interrupts
	ANSELA = 0;
  //For start condition bypass sending out servo signals since there is no data
    PORTA |= LEDn;	//turns off the led
	}