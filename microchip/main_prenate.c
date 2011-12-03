//test

//#include <htc.h>
#include <pic.h>
#include <time.h>
#include "intdefs.h"
#include "uart.h"
#include "spi.h"
#include "timer.h"
#include "inits.h"

#define servoTimeOffset	1200 //1213


#define timer1Compare1_flag	(PIR1 & 0x04)
#define timer1Compare2_flag	(PIR2 & 0x01)
#define timer1Compare3_flag	(PIR3 & 0x10)
#define timer1Compare4_flag	(PIR3 & 0x20)

#define timer1OVF_flag		(PIR1 & 0x01)
#define timer2OVF_flag		(PIR1 & 0x02)
#define timer4OVF_flag		(PIR3 & 0x02)




#define timer1Compare1Enable()	(PIE1 |= 0x04)
#define timer1Compare2Enable()	(PIE2 |= 0x01)
#define timer1Compare3Enable()	(PIE3 |= 0x10)
#define timer1Compare4Enable()	(PIE3 |= 0x20)

#define timer1OVFEnable()	(PIE1 |= 0x01)
#define timer2OVFEnable()	(PIE1 |= 0x02)
#define timer4OVFEnable()	(PIE3 |= 0x02)



#define timer1Compare1Disable()	(PIE1 &= ~0x04)
#define timer1Compare2Disable()	(PIE2 &= ~0x01)
#define timer1Compare3Disable()	(PIE3 &= ~0x10)
#define timer1Compare4Disable()	(PIE3 &= ~0x20)

#define timer1OVFDisable()	(PIE1 &= ~0x01)
#define timer2OVFDisable()	(PIE1 &= ~0x02)
#define timer4OVFDisable()	(PIE3 &= ~0x02)

#define timer1Compare1DisableFlag()	(PIR1 &= ~0x04)
#define timer1Compare2DisableFlag()	(PIR2 &= ~0x01)
#define timer1Compare3DisableFlag()	(PIR3 &= ~0x10)
#define timer1Compare4DisableFlag()	(PIR3 &= ~0x20)

#define timer1OVFDisableFlag()	(PIR1 &= ~0x01)
#define timer2OVFDisableFlag()	(PIR1 &= ~0x02)
#define timer4OVFDisableFlag()	(PIR3 &= ~0x02)


void servoBusInit();
void servoBusManipulate();

uint8_t		servoBus[181][3];
uint8_t		*servoBusPtr;
uint8_t		servoPos[24];
uint8_t		*servoPosPtr;
uint8_t		currentAngle = 0;
uint8_t		servoNum = 0;
volatile uint8_t		freeTime = 0;
volatile uint8_t		bufCnt = 0;

int main() {
	initializations();
	PR4 = 79;

	CCPR1H = timer1StartCnt+1200>>8;
	CCPR1L = 0x00FF & timer1StartCnt+1200;
	CCP1CON = 0x0A;
	timer1Compare1Enable();

	while(servoNum<24){
	servoPos[servoNum] = 90;
	servoNum++;
	}
	servoNum=0;
	servoBusInit();
	servoBusManipulate();
	for(;;) {
		while(freeTime){
			uart_putC('r');
			while(bufCnt<24){
				uart_putC('n');
			}
		servoBusInit();
		servoBusManipulate();
		freeTime = 0;
/*		uint8_t i;
		uart_putC('U');	
		uart_putC(bufCnt);	
		uart_putC('U');
		for(i=0;i<24;i++)uart_putC(servoPos[i]);
*/	
		}
	}
}
void servoBusInit(){
	servoBusPtr = &servoBus;
	while(servoBusPtr<=(&servoBus[180][2]))*(servoBusPtr++) = 0xFF;
}

void servoBusManipulate(){
		uint8_t i;
	
	for(i=23;i>16;i--){
		servoBus[servoPos[i]][0] &= 0xFF^(1<<((i)&0x7)); 
		}
	servoBus[servoPos[16]][0] &= 0xFE; 
	for(i=15;i>8;i--){
		servoBus[servoPos[i]][1] &= 0xFF^(1<<((i)&0x7));
		}
	servoBus[servoPos[8]][1] &= 0xFE; 
	for(i=7;i>0;i--){
		servoBus[servoPos[i]][2] &= 0xFF^(1<<((i)&0x7)); 
		}	
	servoBus[servoPos[0]][2] &= 0xFE; 
		
		uint8_t *_servoBusPtr;//Head,*servoBusPtrHead;
	
	_servoBusPtr = &servoBus[1][0];

	while(_servoBusPtr<=(&servoBus[180][2]))	*(_servoBusPtr)&= *(_servoBusPtr++-3);		
	asm("nop");
}

interrupt isr() {
	//timer 1 ovf 0us
	if (timer1OVF_flag)
    {
        //disable interrupts so timing is not thrown off
        cli();
		
		TMR1 = timer1StartCnt;
		PIR1 &= ~0x01; //clear interrupt flag

		LATC = 0x20;
		LATC = 0x22;//initialize latches
	
		sendServoStartSignal();	
		sendServoStartSignal();	
		sendServoStartSignal();	

	    servoNum = 0;
		currentAngle = 0;
		//dump buffer
//		bufCnt = RCREG;
//		bufCnt = RCREG;
//		bufCnt = RCREG;
		bufCnt = 0;
		servoPosPtr = &servoPos;

		servoBusPtr = &servoBus;
		//reinitialize global interrupts now that time critical events have passed
		PIR3 &= ~0x0A; 
		sei();
    }
	//timer 1 compare 600us
	else if(timer1Compare1_flag){
	cli();
		TMR4 = 0x00;
		T4CON = 0x04;
		timer4OVFEnable();	
		LATC = 0x20;

			do{
			SSP1CON1  &= 0x7F;
			SSP1BUF = *(servoBusPtr++);
			}while(spiConflictFlag);
			do{
			SSP1CON1  &= 0x7F;
			SSP1BUF = *(servoBusPtr++);
			}while(spiConflictFlag);
			do{
			SSP1CON1  &= 0x7F;
			SSP1BUF = *(servoBusPtr++);
			}while(spiConflictFlag);

		LATC = 0x22;
		timer1Compare1DisableFlag();
	sei();	
	}
	//10us 
	else if(timer4OVF_flag){
	cli();
		if(++currentAngle <= 180){

			LATC = 0x20;

			do{
			SSP1CON1  &= 0x7F;
			SSP1BUF = *(servoBusPtr++);
			}while(spiConflictFlag);
			do{
			SSP1CON1  &= 0x7F;
			SSP1BUF = *(servoBusPtr++);
			}while(spiConflictFlag);
			do{
			SSP1CON1  &= 0x7F;
			SSP1BUF = *(servoBusPtr++);
			}while(spiConflictFlag);
			
			LATC = 0x22;
		}
		else{
//		uart_putC('r');	//request servo data 
		freeTime = 1;
		PIE3 &= ~0x02;
		}
		
		//timer4OVFDisableFlag();//get rid of interrupt flag
		PIR3 &= ~0x02;	
	sei();	
	}
//check to see if the uart rx interrupt was triggered
    else if (PIR1 & 0x20) {
	cli();
		servoPos[bufCnt++] = RCREG;
		if(RCSTA & 0x2)PORTA &= ~LEDn;
		PIR1 &= ~0x20; //clear interrupt flag
//		PIR3 &= ~0x02;	
	sei();
    }
}


