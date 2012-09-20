/*
 * clcock.c
 *
 * Created: 5/21/2012 5:28:55 PM
 *  Author: tmartin
 */ 

#include "clock.h"

void clockInit(){
	#ifdef F_CPU
	#if (F_CPU == 32000000)
	OSC.CTRL |= OSC_RC32MEN_bm;
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));
	CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
	#else
	//do nothing 2000000Hz clock enabled by default
	#endif
	#endif
}


