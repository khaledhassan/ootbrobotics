/*
 * adcOpt.h
 *
 * Created: 8/7/2012 9:28:53 PM
 *  Author: Tim
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int16_t adc_data[8][16];

volatile struct cntRegs
{
	uint8_t	CNT			:4;
	uint8_t	reserved	:4;
}adcCnt[8];

uint16_t filterData(int16_t *data);

void adcInit();

uint16_t analogRead(uint8_t pinNum);

#endif /* ADCOPT_H_ */