/*
 * adcInt.h
 *
 * Created: 11/23/2011 7:36:23 PM
 *  Author: Tim
 */ 


#ifndef ADCINT_H_
#define ADCINT_H_

/*
 * adcInt.c
 *
 * Created: 10/29/2011 9:25:47 PM
 *  Author: bfc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

enum _ADC_SOURCE{
		INTERNAL_gc = 0,
		EXTERNAL_gc = 1
};

enum _ADC_EXTERNAL_SOURCES{
		CHANNEL_0	= 0<<3,
		CHANNEL_1	= 1<<3,
		CHANNEL_2	= 2<<3,
		CHANNEL_3	= 3<<3,
		CHANNEL_4	= 4<<3,
		CHANNEL_5	= 5<<3,
		CHANNEL_6	= 6<<3,
		CHANNEL_7	= 7<<3	
};

enum _ADC_INTERNAL_SOURCES{
		TEMP		= 0<<3,
		BANDGAP		= 1<<3,	
		SCALEDVCC	= 2<<3,
		DAC			= 3<<3
};

#define maxFilterSize	32
#define runningFilterSize	8

#if (runningFilterSize > maxFilterSize)
runningFilterSize = maxFilterSize;
#endif

struct RunningAvgFilter{
	uint16_t	* source;
	uint16_t	array[runningFilterSize];
}*runningAvgfilter_t;


struct AnalogData{
		uint16_t data; //last value collected from the channel					
}
//external
ADCA_pin[8],
ADCB_pin[8]//,
//Internal
//temperature,
//bandGap,	
//ScaledVcc,
//dacA,
//dacB
;		


void adcAInit();
void adcBInit();

#endif /* ADCINT_H_ */

