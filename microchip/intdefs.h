#ifndef INTDEFS_H
#define INTDEFS_H

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

#ifndef uint16_t
typedef unsigned int uint16_t;
#endif

#ifndef uint32_t
typedef unsigned long uint32_t;
#endif

//PORTA
#define	TX			1<<0
#define	RX			1<<1
#define SERVO_V		1<<2

#define VIN_V		1<<4
#define LEDn		1<<5

//PORTC
#define	SCK			1<<0
#define	RCK			1<<1
#define	SDO			1<<2
#define	SERVO_REG_T	1<<3
#define	OEn			1<<4
#define	servoOnOff	1<<5

//flags
#define	servoSignalsSent	1<<0	//all servo signals were sent out
#define	recieveFlag			1<<1	//servo data was recieved 
#define processingDone 		1<<2	//servo data was processed for the next cycle
#define sortError			1<<3	//error detected during sorting


#endif