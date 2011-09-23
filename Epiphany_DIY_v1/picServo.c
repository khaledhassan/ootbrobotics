/*
 * picServo.c
 *
 * Created: 7/9/2011 3:09:24 AM
 *  Author: Tim
 */ 


#include "picServo.h"


void setServoAngle(uint8_t data, uint8_t servoNumber){
	if(data > 180)data=180;//prevents erroneous values
	angles[servoNumber-1] = data;
}
uint8_t getServoAngle(uint8_t servoNumber){
	
	return angles[servoNumber-1];
}


void servoControlInit(){
	uartInit(&USARTE0,57600);
	uint8_t i;
	PMIC.CTRL = PMIC_MEDLVLEN_bm;
	//initializes global interrupts.  This is required to make the servo controller work.
	sei();
	//This for loop initializes all the servos to 90 degrees at startup.  If this is not preferable
	//just set the angle to something different for all the servos, or individuals for that matter.	
	for(i=0;i<24;i++)angles[i] = 90;
	
	/*  DMA.CH0.CTRLA = DMA_CH_ENABLE_bm | DMA_CH_SINGLE_bm;//| DMA_CH_REPEAT_bm;
		DMA.CH0.ADDRCTRL = DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_INC_gc; //set the params for source reload and fix the destination 
		DMA.CH0.TRIGSRC = 0x8B; //set trigger of DMA to USARTE0 RX interrupt
		DMA.CH0.TRFCNT = 24;
		
		DMA.CH0.SRCADDR2 = (uint8_t)((&angles)>>16);
		DMA.CH0.SRCADDR1 = (uint8_t)(0xFF & ((&angles)>>8));
		DMA.CH0.SRCADDR0 = (uint8_t)(0xFF & (&angles));
		
		DMA.CH0.DESTADDR2 = (uint8_t)((&USARTE0.DATA)>>16);
		DMA.CH0.DESTADDR1 = (uint8_t)(0xFF & ((&USARTE0.DATA)>>8));
		DMA.CH0.DESTADDR0 = (uint8_t)(0xFF & (&USARTE0.DATA));
		
		DMA.CTRL |= DMA_ENABLE_bm;	//enable DMA
		*/
	
}

ISR(USARTE0_RXC_vect){
	cli();	//diables interrupts so that this code is not disturbed
	uint16_t temp = stdout;	//temp is used to preserve the current device being used by stdout.
	stdout = &uartE0_str;	//now the pic can be spoken to
	char msg = USARTE0.DATA; //read in the data from the pic.
	
	//first byte that is sent
	if(msg == 'r'){
		printf("%c",angles[23]);
		currentAngle = 0;
	} 
	//for ever byte thereafter
	else if(msg == 'n')
	{
		printf("%c",angles[currentAngle++]);
	}
	//used for error handling
	else 
	{		
		printf("%c",msg);
	}
	stdout = temp;	//Puts stdout back to the way it was.
	sei();//re-enables interrupts now that the routine is finished.
}
