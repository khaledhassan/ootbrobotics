/*
 * picServo.h
 *
 * Created: 7/9/2011 3:09:39 AM
 *  Author: Tim
 */ 


#ifndef PICSERVO_H_
#define PICSERVO_H_

#include <stdbool.h>
#include <asf.h>
#include <stdio.h>
#include "uart.h"

#define updateMsgHeader	0x55
#define controlHeader	0xCC

volatile uint8_t angles[24];//this is the array that holds all of the data used for controlling servos

volatile uint8_t currentAngle;//current angle being pointed to by the servo control code

void setServoAngle(uint8_t data, uint8_t servoNumber);//use this function to set a new angle for the servo to go to
uint8_t getServoAngle(uint8_t servoNumber);//use this function to get the angle the servo is currently at
void servoControlInit(void);/*used to initialize the servo control unit*/
//void sendServoUpdateMsg(void);


#endif /* PICSERVO_H_ */