/*
 * RTC.h
 *
 * Created: 7/8/2011 12:32:30 AM
 *  Author: Tim
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <asf.h>
#include <avr/io.h>

#define delayNotOver	(!RTC.INTFLAGS & RTC_OVFIF_bm)	//used to tell if the RTC delay time has elapsed
#define delayOver		(RTC.INTFLAGS & RTC_OVFIF_bm)	//used to tell if the RTC delay time has elapsed


void RTC_Delay_ms(uint16_t delayTime);/*this function is used to declare a delay time.  It does not stop code you must pole whether the delay has ended.  This is useful because there is no dead time waiting in a delay loop.*/
void RTC_DelayInit(void);/*this function initializes the RTC(Real Time Clock) module */

#endif /* RTC_H_ */