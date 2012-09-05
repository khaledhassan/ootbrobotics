/*
 * motorNew.h
 *
 * Created: 8/7/2012 10:06:44 PM
 *  Author: Tim
 */ 

#include <avr/io.h>

#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_PERIOD_gc			1024	//This is the maximum value for PWM.  Duty cycle is (value/1024)*100%
#define Motor_CLKSEL_DIV_gc		TC_CLKSEL_DIV1_gc	//setting of a division of 1 prescaler.  So in other words there is no prescaler  

typedef enum motorDirection_enum{
	MOTOR_DIR_NEUTRAL	= 0,
	MOTOR_DIR_FORWARD	= 1,
	MOTOR_DIR_BACKWARD	= 2	
}motorDirection_t;

typedef enum motorDirectionHP_enum{
	MOTOR_DIR_NEUTRAL_HP	= 0,
	MOTOR_DIR_FORWARD_HP	= 5,
	MOTOR_DIR_BACKWARD_HP	= 0xA	
}motorDirectionHP_t;

typedef struct motor0Dir_field{
	motorDirection_t	direction	:2;
	uint8_t				res1		:2;
	uint8_t				res2		:2;
	uint8_t				res3		:2;
}m1Dir_t;

typedef struct motor1Dir_field{
	uint8_t				res0		:2;
	motorDirection_t	direction	:2;
	uint8_t				res2		:2;
	uint8_t				res3		:2;
}m2Dir_t;

typedef struct motor2Dir_field{
	uint8_t				res0		:2;
	uint8_t				res1		:2;
	motorDirection_t	direction	:2;
	uint8_t				res3		:2;
}m3Dir_t;

typedef struct motor3Dir_field{
	uint8_t				res0		:2;
	uint8_t				res1		:2;
	uint8_t				res2		:2;
	motorDirection_t	direction	:2;
}m4Dir_t;

typedef struct motor1DirHP_field{
	motorDirection_t	direction	:4;
	uint8_t				res1		:4;
}m1DirHP_t;

typedef struct motor2DirHP_field{
	uint8_t				res0		:4;
	motorDirection_t	direction	:4;
}m2DirHP_t;

typedef struct motorControl0{
	uint16_t	*effortLevel;
	m1Dir_t		*ctrlReg;
}motorControl1_t;

typedef struct motorControl1{
	uint16_t	*effortLevel;
	m2Dir_t		*ctrlReg;
}motorControl2_t;

typedef struct motorControl2{
	uint16_t	*effortLevel;
	m3Dir_t		*ctrlReg;
}motorControl3_t;

typedef struct motorControl3{
	uint16_t	*effortLevel;
	m4Dir_t		*ctrlReg;
}motorControl4_t;

typedef struct motorControl1HP{
	uint16_t	*effortLevel1;
	uint16_t	*effortLevel2;
	m1DirHP_t		*ctrlReg;
}motorControl1HP_t;

typedef struct motorControl2HP{
	uint16_t	*effortLevel1;
	uint16_t	*effortLevel2;
	m2DirHP_t		*ctrlReg;
}motorControl2HP_t;

void motorInit();
void setMotorEffort(uint8_t motorNum, uint16_t effort, motorDirection_t motorDir);
void setMotorEffort_HP(uint8_t hpMotorNum, uint16_t effort, motorDirectionHP_t motorDir);

#endif /* MOTORNEW_H_ */