/*
 * motor.c
 *
 * Created: 7/2/2011 1:13:25 AM
 *  Author: Tim
 */ 

#include "motor.h"

void motorInit(void){
	
	//set motor period for 1024... 32000000/1024 = 31.25kHz PWM.  this frequency is above audible

	TCF0.PER = MOTOR_PERIOD_gc;
	TCF0.CTRLA = Motor_CLKSEL_DIV_gc;
#if (F_CPU == 2000000L)
#warning "F_CPU is defined as 2MHz this will make motors whine and sound annoying"	
#endif
	
	/*enable the motor control lines and single slope PWM
	and initialize motor speed as zero*/
	
#if (motorCtrlMode == quadMode)
	TCF0.CTRLB = TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm | TC_WGMODE_SS_gc;
	TCF0.CCA = 0;
	TCF0.CCB = 0;
	TCF0.CCC = 0;
	TCF0.CCD = 0;
#elif (motorCtrlMode == dualModeDoubleChip)
	TCF0.CTRLB = TC0_CCBEN_bm | TC0_CCDEN_bm | TC_WGMODE_SS_gc;
	TCF0.CCB = 0;
	TCF0.CCD = 0;
#elif (motorCtrlMode == dualModeSingleChip)
	TCF0.CTRLB = TC0_CCCEN_bm | TC0_CCDEN_bm | TC_WGMODE_SS_gc;	
	TCF0.CCC = 0;
	TCF0.CCD = 0;
#else
	//do nothing because motor control is disconnected
#endif	
}

void setMotorDuty(uint8_t motorNumber, uint16_t duty,uint8_t direction){
	
	motorNumber--;//this fixes the error of the silkscreen vs code numbering
	if (duty>MOTOR_PERIOD_gc) duty = MOTOR_PERIOD_gc;
	
	switch (motorNumber)
	{
	case (0):
		TCF0.CCA = duty;
		PORTK.OUTSET = direction<<(motorNumber<<1);	
		PORTK.OUTCLR = 0x3<<(motorNumber<<1) & (~direction)<<(motorNumber<<1);	
		break;
	case (1):
		TCF0.CCB = duty;
		PORTK.OUTSET = direction<<(motorNumber<<1);	
		PORTK.OUTCLR = 0x3<<(motorNumber<<1) & (~direction)<<(motorNumber<<1);	
		break;
	case (2):
		TCF0.CCC = duty;
		PORTK.OUTSET = direction<<(motorNumber<<1);	
		PORTK.OUTCLR = 0x3<<(motorNumber<<1) & (~direction)<<(motorNumber<<1);	
		break;
	case (3):
		TCF0.CCD = duty;
		PORTK.OUTSET = direction<<(motorNumber<<1);	
		PORTK.OUTCLR = 0x3<<(motorNumber<<1) & (~direction)<<(motorNumber<<1);	
		break;
	default:
		//do nothing motor number was incorrectly specified
		break;				
	}
}