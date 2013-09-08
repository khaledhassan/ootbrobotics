/*
 * RTC.c
 *
 * Created: 7/8/2011 12:31:53 AM
 *  Author: Tim
 */ 
#include "RTC.h"

void RTC_DelayInit()
{
	while(RTC.STATUS & RTC_SYNCBUSY_bm);
	CLK.RTCCTRL |= CLK_RTCEN_bm | CLK_RTCSRC_RCOSC32_gc;

	RTC.CTRL = RTC_PRESCALER_DIV1_gc;
	RTC.CNT = 0;
	//hack to make delayOver true from the get go
	RTC_Delay_ms(1);
}

void RTC_Delay_ms(uint16_t delayTime){
	while(RTC.STATUS & RTC_SYNCBUSY_bm);
	RTC.INTFLAGS |= RTC_OVFIF_bm;
	delayTime+=delayTime/40;
	RTC.PER = delayTime;
	RTC.CNT = 0;
}

