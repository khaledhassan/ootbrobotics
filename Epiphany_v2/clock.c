/*
 * clcock.c
 *
 * Created: 5/21/2012 5:28:55 PM
 *  Author: tmartin
 */ 

#include "utility.h"
#include "clock.h"


void clockInit()
{	
	OSC.CTRL |= OSC_RC32MEN_bm | OSC_RC32KEN_bm;
	while(!(OSC.STATUS & OSC_RC32MRDY_bm) || !(OSC.STATUS & OSC_RC32KRDY_bm));


	CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;

	OSC.RC32KCAL = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, RCOSC32K) );

	DFLLRC32M.CALB = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, RCOSC32M) );
	DFLLRC32M.CALA = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, RCOSC32MA) );
	
	OSC.DFLLCTRL = OSC_RC32MCREF_RC32K_gc;

	DFLLRC32M.CTRL |= DFLL_ENABLE_bm;
	DFLLRC32M.COMP0 = 0x12;
	DFLLRC32M.COMP1 = 0x7A;

	//enable real time clock
//	while(RTC.STATUS & RTC_SYNCBUSY_bm);
//	CLK.RTCCTRL |= CLK_RTCEN_bm | CLK_RTCSRC_RCOSC32_gc;
}


