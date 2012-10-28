/*
 * ATtinyServo.c
 *
 * Created: 11/13/2011 3:16:16 PM
 *  Author: bfc
 */ 

#include "ATtinyServo.h"

#define servoRefresh

//125000
#define BAUD125000	1984		
#define USART_BAUDCTRLA_125000	BAUD125000
#define USART_BAUDCTRLB_125000	0xA0 | (uint16_t)(0x0FFF & BAUD125000>>8)
#define USART_CTRLB_125000		USART_TXEN_bm | USART_CLK2X_bm

//57600
#define BAUD57600	2190			
#define USART_BAUDCTRLA_57600	BAUD57600
#define USART_BAUDCTRLB_57600	0xB0 | (uint16_t)(0x0FFF & BAUD57600>>8)
#define USART_CTRLB_57600		USART_TXEN_bm | USART_CLK2X_bm



#define numOfServos				24					//there are 24 dedicated servo channels on the Epiphany DIY
#define servoBufferSize			4*numOfServos+1 + 128	//each servo command takes 4 bytes: (1)servoNumber (2-3)servoTime(16-bit) and (4) the check (servoNumber | 0x80) 
#define	servoRefreshThreshold	1					//this sets the number of cycles of the 20ms timer corresponding to a servos idle time being too long

#define defaultMinimumAngleTime		600*1.5			//this corresponds to the amount of dead time corresponding to a servo's minimum angle of 0 degrees
#define defaultMaximumAngleTime     (1500+900)*1.5	//this corresponds to the amount of time corresponding to a servo's maximum angle of 180 degrees
#define timerTicksPerDegree				15			//how many ticks in the ATiny's timer corresponding to 1 degree of angular displacement at the servo

FILE	servoBufferFile = FDEV_SETUP_STREAM(servo_putchar,NULL,_FDEV_SETUP_WRITE);

struct ServoBuffer{
	const uint8_t *bufferBegin;
	const uint8_t *bufferEnd;
	uint8_t *head;
	uint8_t *tail;
	uint8_t data[servoBufferSize];
}servoBuffer;

void ATtinyServoInit(void)
{
	PORTE.DIRSET = 0x08;//enable tx line as an output	
	PORTE.DIRCLR = 0x04;//enable this pin as an input 
	servoBuffer.bufferEnd = &servoBuffer.data[servoBufferSize-1];	
	servoBuffer.bufferBegin = &servoBuffer.data[0];
	servoBuffer.head = servoBuffer.bufferBegin;
	servoBuffer.tail = servoBuffer.bufferBegin;
	
	USARTE0.CTRLB = USART_CTRLB_125000;
	USARTE0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
	USARTE0.BAUDCTRLA = USART_BAUDCTRLA_125000;
	USARTE0.BAUDCTRLB = USART_BAUDCTRLB_125000;

	PORTE.PIN2CTRL = PORT_ISC_BOTHEDGES_gc | PORT_OPC_PULLDOWN_gc;
	PORTE.INTCTRL = PORT_INT0LVL_LO_gc;
	PORTE.INT0MASK = 0x04;	//interrupt on the pin change of PORTE6
	
	TCE1.PER = 10000;					//set period for 10000 which will lend to a 50Hz overflow
	TCE1.CTRLA = TC_CLKSEL_DIV64_gc;	//set the prescaler for 50Hz overflow
	TCE1.CTRLB = TC_WGMODE_SS_gc;		//set timer to single slope operation.  So it counts up then counts up agian etc.
	TCE1.INTCTRLA = TC_OVFINTLVL_LO_gc;	//set a low level interrupt for servicing servos
	PMIC.CTRL |= PMIC_LOLVLEN_bm; 
	
	uint8_t i;
	for(i=0;i<24;i++)
	{
		servo[i].configReg.params.enabled = false;	//the board uses numbers 1 to 24 while the code is written for 0 to 23
		servo[i].servoTime = 0;						//this is how the ATtiny knows the servo is deactivated
		servo[i].configReg.params.upToDate = true;	//this is used similar to that of enabled servos		
	}
	
}

void servo_putchar(char c,FILE *unused)
{
	storeServo(c);
}

int servo_getchar(FILE *stream){
uint8_t temp1;

	if (servoBuffer.tail == servoBuffer.bufferEnd){
		uint8_t temp = *servoBuffer.tail;
		*servoBuffer.tail = 0;
		servoBuffer.tail = servoBuffer.bufferBegin;
		while(!(USARTE0.STATUS & USART_DREIF_bm));
		USARTE0.DATA = temp;	


	}
	//else return *servoBuffer.tail++;
	else{
		while(!(USARTE0.STATUS & USART_DREIF_bm));
		USARTE0.DATA = *servoBuffer.tail;
		temp1 = *servoBuffer.tail;
		*servoBuffer.tail++ = 0;
	
	}
}

void storeServo(char c){
	if(servoBuffer.head == servoBuffer.bufferEnd){
		*servoBuffer.head = c;
		servoBuffer.head = servoBuffer.bufferBegin;	
	}		
	else *servoBuffer.head++ = c;
}

uint8_t dataInServoBuffer(void){
	if(servoBuffer.head == servoBuffer.tail) return 0;	//no data to be read
	else return 1;	
}


//Occurs upon Interrupt request from the Attiny
ISR(PORTE_INT0_vect){	
	cli();
	if(dataInServoBuffer())	servo_getchar(NULL); //grabs the next byte from the servoBuffer	
	sei();
}

ISR(TCE1_OVF_vect){
	cli();
	uint8_t i;		//simple increment var
	for(i=0;i<24;i++)
	{

	//for less impact logic could be implemented to poll the enable flag to refresh these servo channels at a slower rate.	

		//if the servo is up to date increment its idle cycles at that state
		if(servo[i].configReg.params.upToDate){
				
#ifdef servoRefresh
			servo[i].configReg.statusReg++;	//the idle cycles bit field is at the bottom of the reg.  
											//So an increment to the reg will increment the idle cycles
											//only as long as the range of increments is kept in check ie it stays under 31	
																							
			//if the servo has been idle for too long set it as out of date so it can be refreshed
			if(servo[i].configReg.statusReg & 0x1F >= servoRefreshThreshold)servo[i].configReg.params.upToDate = false;
#endif
		}			
		//now if the servo is out of date we need to send its message to the servoBuffer
		else 
		{
		//print servoNumber, time high. time low, 0x80 | servoNumber
			fprintf(&servoBufferFile,"%c%c%c%c",i, (servo[i].servoTime >>8), servo[i].servoTime, (i | 0x80));
			servo[i].configReg.statusReg = 0xC0 + i;	//this will clear the idleCyclesCount, set the servo as upToDate and preserve the enabled bit.
		//	servo[i].configReg.params.upToDate = true;
		//	servo[i].configReg.params.enabled = true;
		}
		
	}
	
	sei();
	
}

void disableServo(uint8_t servoNumber){
	servo[--servoNumber].configReg.params.enabled = false;	//the board uses numbers 1 to 24 while the code is written for 0 to 23
	servo[servoNumber].servoTime = 0;						//this is how the ATtiny knows the servo is deactivated
	servo[servoNumber].configReg.params.upToDate = false;	//this is used similar to that of enabled servos
}

void setServoAngle(uint8_t servoNumber,uint8_t angle){
	if(angle>180)angle = 180;
	
	//later implementations should take servo type into account. For their separate timings
	
	//also minimumAngleTime should be configurable in later revisions

//this is a default implementation
	
	//--servonumber compensates for the mismatch between code numbering and the pcb labeling 0-23 vs 1-24
	servo[--servoNumber].servoTime = defaultMinimumAngleTime + angle*timerTicksPerDegree; //600us (0 degrees) + angle displacement time  
	servo[servoNumber].configReg.params.enabled = true;		//if the servo wasn't enabled it is now
	servo[servoNumber].configReg.params.upToDate = false;	//this says that the servo should be updated immediately.
}

void setServoPosition(uint8_t servoNumber, uint16_t servoPosition){
	
	if(servoPosition < defaultMinimumAngleTime) servoPosition = defaultMinimumAngleTime;
	else if(servoPosition > defaultMaximumAngleTime)servoPosition = defaultMaximumAngleTime;
	servo[--servoNumber].servoTime = servoPosition;
	servo[servoNumber].configReg.params.enabled = true;		//if the servo wasn't enabled it is now
	servo[servoNumber].configReg.params.upToDate = false;	//this says that the servo should be updated immediately.
}

uint8_t getServoAngle(uint8_t servoNumber){
	return (uint8_t) (servo[--servoNumber].servoTime - defaultMinimumAngleTime)/timerTicksPerDegree;
}

uint16_t getServoPosition(uint8_t servoNumber){
	return (uint16_t) (servo[--servoNumber].servoTime);
}

	