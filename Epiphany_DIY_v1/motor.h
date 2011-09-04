/*
 * motor.h
 *
 * Created: 7/2/2011 1:13:38 AM
 *  Author: Tim
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <asf.h>

#define MOTOR_PERIOD_gc			1024	//This is the maximum value for PWM.  Duty cycle is (value/1024)*100%
#define Motor_CLKSEL_DIV_gc		TC_CLKSEL_DIV1_gc	//setting of a division of 1 prescaler.  So in other words there is no prescaler  

#define MOTOR_DIR_NEUTRAL_gc	0		//disables braking, and control of the motor
#define MOTOR_DIR_FORWARD_gc	1		//configures the motor for forward drive assuming your wiring is correct
#define MOTOR_DIR_BACKWARD_gc	2		//configures the motor for backward drive assuming your wiring is correct
#define MOTOR_DIR_BRAKE_gc		3		/*brakes the motor quickly.  This may cause amperage spikes due to motors being an inductive load
										  use with caution.*/
void motorInit(void);					//this function reinitializes the motor driving modules of the Epiphany DIY 
void setMotorDuty(uint8_t motorNumber, uint16_t duty,uint8_t direction);/*This function is used to set the duty of a motor.  MotorNumber is the motor in question duty is a misnomer because it is not the % duty but a disticnt value 0-1024.  The direction can be specified easily by defines I have created Motor_DIR_..._gc */
#endif /* MOTOR_H_ */