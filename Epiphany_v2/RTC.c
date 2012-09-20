/*
 * RTC.c
 *
 * Created: 7/8/2011 12:31:53 AM
 *  Author: Tim
 */ 
#include "RTC.h"

void RTC_DelayInit()
{
	RTC.CTRL = RTC_PRESCALER_DIV1_gc;
	RTC.CNT = 0;
}

void RTC_Delay_ms(uint16_t delayTime){
	RTC.INTFLAGS |= RTC_OVFIF_bm;
	delayTime+=delayTime/40;
	RTC.PER = delayTime;
	RTC.CNT = 0;
}

