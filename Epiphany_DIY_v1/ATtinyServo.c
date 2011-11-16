/*
 * ATtinyServo.c
 *
 * Created: 11/13/2011 3:16:16 PM
 *  Author: bfc
 */ 

#include "ATtinyServo.h"

void ATtinyServoInit(void){
	//setup uart
	uartInit(&USARTE0,230400);
	USARTE0DMASetup();
}

void DMAEnable(void){	
	DMA.CTRL |= DMA_ENABLE_bm;
}

void DMADisable(void){	
	DMA.CTRL &= ~DMA_ENABLE_bm;
}

void USARTE0DMASetup(void){

uint8_t i;
for(i=0;i<24;i++)setServoTime(i,2250);

DMAEnable();
	
DMA.CH0.CTRLA |= DMA_CH_BURSTLEN_1BYTE_gc;
DMA.CH0.ADDRCTRL |= DMA_CH_SRCRELOAD_BLOCK_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_NONE_gc | DMA_CH_DESTDIR_FIXED_gc;
DMA.CH0.TRIGSRC = DMA_CH_TRIGSRC_USARTE0_DRE_gc;


//this is where I would point the DMA to the source ie. the servoData structure
uint32_t temp = &servo;
DMA.CH0.SRCADDR0 =0xFF & temp;
DMA.CH0.SRCADDR1 =(0xFF00 & temp)>>8;
DMA.CH0.SRCADDR2 =(0xFF0000 & temp)>>16;



DMA.CH0.TRFCNTL = 24*4;
DMA.CH0.TRFCNTH = 0;


//points to the uarte0 data reg
DMA.CH0.DESTADDR0 =0xA0;
DMA.CH0.DESTADDR1 =0x0A;
DMA.CH0.DESTADDR2 =0;

DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;

}

void setServoTime(uint8_t servoNumber,uint16_t servoTime){
	//servos are numbered 0-23 in code and 1-24 in reality.  So servoNumber - 1 is appropriate
	servo[servoNumber - 1].timerVal = servoTime;
}

uint8_t getServoAngle(uint8_t servoNumber, enum SERVO_TYPE servoType){
	/*
	the servo window is 20ms (50Hz) and the ATtiny4313 has a 12MHz crystal a divide by 8 prescaler is used for timer1
	
	12.0E6 HZ/50Hz/8 = 30000 timer cycles per 20ms (1.5 timer cycles = 1us)
	
	*/ 
	//servo[servoNumber - 1].timerVal
}
uint16_t getServoTime(uint8_t servoNumber){}