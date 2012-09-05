/*
 * adcOpt.h
 *
 * Created: 8/7/2012 9:28:53 PM
 *  Author: Tim
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adcInit(ADC_t	*adcModule);
void adcChannelMux(ADC_t *adcModule, uint8_t channelNum, uint8_t inputPin);
uint16_t analogRead(ADC_t *adcModule, uint8_t channelNum);

#endif /* ADCOPT_H_ */