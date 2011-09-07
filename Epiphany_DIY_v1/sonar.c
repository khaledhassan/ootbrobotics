/*
 * sonar.c
 *
 * Created: 9/7/2011 4:16:02 AM
 *  Author: Tim
 */ 

#include "sonar.h"

void sonarAssignment(PORT_t *port, uint8_t pin, uint8_t sonarNumber){
	sonar[sonarNumber].sonarPin = pin;
	sonar[sonarNumber].sonarPort = port;
}

void sonarInit()
{
	//speed of sound is 343.2 m/s and the range is 3m for the Ping))). so max time <9ms
	//1/.009 ~111Hz.  32000000/111 = 288288 cpu cyles per ~longest time interval to read.
	// the timers have a maximum resolution of 16-bit = 65536. 288288/65536 = 4 and change
	//the next prescaler above 4 is selected "8"

	TCE1.CTRLA = TC_CLKSEL_DIV8_gc;
	TCE1.CTRLB = TC_WGMODE_NORMAL_gc | TC1_CCAEN_bm;				//disable pwm generation
	TCE1.CTRLD = TC_EVSEL_CH0_gc | TC_EVACT_PW_gc;	//select channel 0 as the source and the action pulse width		
	TCE1.INTCTRLA = TC_CCAINTLVL_LO_gc;
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
}

void sonarEnable(struct Sonar *_sonar){

	if (_sonar->sonarPin > 7)return;  //if you get here you screwed up
	
	EVSYS.CH0MUX = (((uint16_t)_sonar->sonarPort>>2) & 0x38) + (EVSYS_CHMUX_PORTA_PIN0_gc | _sonar->sonarPin);		//sets portE pin 0 to the event channel 0. 

	*(&(_sonar->sonarPort->PIN0CTRL) + _sonar->sonarPin) &= 0xFF & PORT_ISC_BOTHEDGES_gc;	//set pincntrl of the event pin to sense changes of both rising and falling

	TCE1.CTRLB |=TC1_CCAEN_bm;
	currentSonarPtr = _sonar;
}

void disableAllSonar(void){
	TCE1.CTRLB &= 0xFF & ~TC1_CCAEN_bm;
	TCE1.INTCTRLA = 0;
}	

ISR(TCE1_CCA_vect){
	//update value
	currentSonarPtr->rawTime = TCE1.CCA;
}
