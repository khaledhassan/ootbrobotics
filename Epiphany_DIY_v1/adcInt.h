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

enum ADC_SOURCE{
		INTERNAL_gc = 0,
		EXTERNAL_gc = 1
};

enum ADC_EXTERNAL_SOURCES{
		CHANNEL_0	= 0,
		CHANNEL_1	= 1,
		CHANNEL_2	= 2,
		CHANNEL_3	= 3,
		CHANNEL_4	= 4,
		CHANNEL_5	= 5,
		CHANNEL_6	= 6,
		CHANNEL_7	= 7		
};

enum ADC_INTERNAL_SOURCES{
		TEMP		= 0,
		BANDGAP		= 1,	
		SCALEDVCC	= 2,
		DAC			= 3
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
ADCB_pin[8],
//Internal
temperature,
bandGap,	
ScaledVcc,
dacA,
dacB
;		


void adcAInit();

#endif /* ADCINT_H_ */