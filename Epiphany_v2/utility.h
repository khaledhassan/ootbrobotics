/*
 * utility.h
 *
 * Created: 8/27/2013 7:19:22 PM
 *  Author: Tim
 */ 


#ifndef UTILITY_H_
#define UTILITY_H_


#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stddef.h>
#include <avr/pgmspace.h>

uint8_t ReadCalibrationByte( uint8_t index );

#ifndef __AVR_ATxmega32A4U__

#define dbledInit() PORTR.DIRSET = 2
#define dbledTgl()	PORTR.OUTTGL = 2
#define dbledOn()	PORTR.OUTCLR = 2
#define dbledOff()	PORTR.OUTSET = 2

#else

#define dbledInit() PORTC.DIRSET = 0
#define dbledTgl()	PORTC.OUTTGL = 0
#define dbledOn()	PORTC.OUTCLR = 0
#define dbledOff()	PORTC.OUTSET = 0

#endif

#endif /* UTILITY_H_ */