/*
 * motorNew.c
 *
 * Created: 8/7/2012 10:06:20 PM
 *  Author: Tim
 */ 

#include "motor.h"

extern motorControl1_t motor1 = {&TCF0.CCA,&PORTK.OUT};
extern motorControl2_t motor2 = {&TCF0.CCB,&PORTK.OUT};
extern motorControl3_t motor3 = {&TCF0.CCC,&PORTK.OUT};
extern motorControl4_t motor4 = {&TCF0.CCD,&PORTK.OUT};
	
extern motorControl1HP_t hpMotor1 = {&TCF0.CCA,	&TCF0.CCB, &PORTK.OUT};
extern motorControl2HP_t hpMotor2 = {&TCF0.CCC,	&TCF0.CCD, &PORTK.OUT};
	
	
void motorInit()
{

	TCF0.PER = MOTOR_PERIOD_gc;
	TCF0.CTRLA = Motor_CLKSEL_DIV_gc;
	TCF0.CTRLB = TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm | TC_WGMODE_SS_gc;

	motor1.ctrlReg->direction = MOTOR_DIR_NEUTRAL;
	motor2.ctrlReg->direction = MOTOR_DIR_NEUTRAL;
	motor3.ctrlReg->direction = MOTOR_DIR_NEUTRAL;
	motor4.ctrlReg->direction = MOTOR_DIR_NEUTRAL;
	
	PORTK.DIRSET = 0xFF;	
	
	PORTF.DIRSET = 0x0F;
}

void setMotorEffort(uint8_t motorNum, uint16_t effort, motorDirection_t motorDir)
{
	switch(motorNum)
	{
		case(1):
			motor1.ctrlReg->direction	= motorDir;
			*motor1.effortLevel			= effort;
		break;
		
		case(2):
			motor2.ctrlReg->direction	= motorDir;
			*motor2.effortLevel			= effort;
		break;
		
		case(3):
			motor3.ctrlReg->direction	= motorDir;
			*motor3.effortLevel			= effort;
		break;
		
		case(4):
			motor4.ctrlReg->direction	= motorDir;
			*motor4.effortLevel			= effort;
		break;
	}
}

void setMotorEffort_HP(uint8_t hpMotorNum, uint16_t effort, motorDirectionHP_t motorDir)
{
	switch(hpMotorNum)
	{
		case(1):
*			hpMotor1.effortLevel1			= effort;
*			hpMotor1.effortLevel2			= effort;
			hpMotor1.ctrlReg->direction		= motorDir;
		break;
		
		case(2):
*			hpMotor2.effortLevel1			= effort;
*			hpMotor2.effortLevel2			= effort;
			hpMotor2.ctrlReg->direction		= motorDir;
		break;
	}
}
	