/*
 * adcOpt.c
 *
 * Created: 8/7/2012 9:28:39 PM
 *  Author: Tim
 */ 

#include "adc.h"

void adcInit(ADC_t	*adcModule)
{
	adcModule->CH0.MUXCTRL = ADC_CH_MUXPOS_PIN0_gc;
	adcModule->CH1.MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;
	adcModule->CH2.MUXCTRL = ADC_CH_MUXPOS_PIN2_gc;
	adcModule->CH3.MUXCTRL = ADC_CH_MUXPOS_PIN3_gc;
	
	adcModule->CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	adcModule->CH1.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	adcModule->CH2.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	adcModule->CH3.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	
	adcModule->CTRLA = ADC_CH3START_bm | ADC_CH2START_bm | ADC_CH1START_bm | ADC_CH0START_bm | ADC_ENABLE_bm; //enable adc and all its channels
	adcModule->CTRLB = ADC_FREERUN_bm;//set to freerun
	adcModule->EVCTRL = ADC_SWEEP_0123_gc;//sweel all channels	
	adcModule->PRESCALER = ADC_PRESCALER_DIV128_gc;
	
	adcModule->REFCTRL = ADC_REFSEL_VCC_gc | ADC_BANDGAP_bm | ADC_TEMPREF_bm;
}

void adcChannelMux(ADC_t *adcModule, volatile uint8_t channelNum, uint8_t inputPin)
{
	
	switch(channelNum)
	{
		case(0):
			adcModule->CH0.MUXCTRL = (inputPin & 0x7)<<3;
		break;
		
		case(1):
			adcModule->CH1.MUXCTRL = (inputPin & 0x7)<<3;
		break;
		
		case(2):
			adcModule->CH2.MUXCTRL = (inputPin & 0x7)<<3;
		break;
		
		case(3):
			adcModule->CH3.MUXCTRL = (inputPin & 0x7)<<3;
		break;
	}
}

uint16_t analogRead(ADC_t *adcModule, uint8_t channelNum)
{
	switch(channelNum)
	{
		case(0):
			return adcModule->CH0.RES;
		break;
				
		case(1):
			return adcModule->CH1.RES;
		break;
		
		case(2):
			return adcModule->CH2.RES;
		break;
		
		case(3):
			return adcModule->CH3.RES;
		break;
	}
}