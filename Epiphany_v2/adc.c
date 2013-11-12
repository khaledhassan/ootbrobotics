/*
 * adcOpt.c
 *
 * Created: 8/7/2012 9:28:39 PM
 *  Author: Tim
 */ 

#include "adc.h"
#include "utility.h"


void adcInit()
{
	
	ADCA.CALL = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0) );
	ADCA.CALH = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1) );

	ADCA.CTRLB = 
						ADC_CURRLIMIT_NO_gc		|
						ADC_CONMODE_bm			|	//enable signed mode
						ADC_FREERUN_bm			|
						ADC_RESOLUTION_12BIT_gc	;
					
	ADCA.REFCTRL =		ADC_REFSEL_VCC_gc;			//utilize the vref of vcc/1.6 = 2.0625 V
	
	ADCA.PRESCALER =	ADC_PRESCALER_DIV512_gc;		
	
	//set all the adc channels to be single ended inputs	
	ADCA.CH0.CTRL =		ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH1.CTRL =		ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH2.CTRL =		ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH3.CTRL =		ADC_CH_INPUTMODE_SINGLEENDED_gc;
	
	//analog channels 0-3 will correlate to the analog pins 0-3 on port A
	ADCA.CH0.MUXCTRL =	ADC_CH_MUXPOS_PIN0_gc;
	ADCA.CH1.MUXCTRL =	ADC_CH_MUXPOS_PIN1_gc;
	ADCA.CH2.MUXCTRL =	ADC_CH_MUXPOS_PIN2_gc;
	ADCA.CH3.MUXCTRL =	ADC_CH_MUXPOS_PIN3_gc;
	
	//initialize conversion complete interrupts on all ADCA channel inputs
	ADCA.CH0.INTCTRL =	ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;	
	ADCA.CH1.INTCTRL =	ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;
	ADCA.CH2.INTCTRL =	ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;
	ADCA.CH3.INTCTRL =	ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;
	
	ADCA.EVCTRL =		ADC_SWEEP_0123_gc;
	
	//enable ADCA, and start conversions on all channels
	ADCA.CTRLA =		ADC_ENABLE_bm	|
						ADC_CH0START_bm	|
						ADC_CH1START_bm	|
						ADC_CH2START_bm	|
						ADC_CH3START_bm	;

	ADCB.CALL = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, ADCBCAL0) );
	ADCB.CALH = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, ADCBCAL1) );
	
	ADCB.CTRLB =
						ADC_CURRLIMIT_NO_gc		|
						ADC_CONMODE_bm			|	//enable signed mode
						ADC_FREERUN_bm			|
						ADC_RESOLUTION_12BIT_gc	;
	
	ADCB.REFCTRL =		ADC_REFSEL_VCC_gc;			//utilize the vref of vcc/1.6 = 2.0625 V
	
	ADCB.PRESCALER =	ADC_PRESCALER_DIV512_gc;		
	
	//set all the adc channels to be single ended inputs
	ADCB.CH0.CTRL =		ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCB.CH1.CTRL =		ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCB.CH2.CTRL =		ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCB.CH3.CTRL =		ADC_CH_INPUTMODE_SINGLEENDED_gc;
	
	//analog channels 0-3 will correlate to the analog pins 4-7 on port A
	ADCB.CH0.MUXCTRL =	ADC_CH_MUXPOS_PIN12_gc;
	ADCB.CH1.MUXCTRL =	ADC_CH_MUXPOS_PIN13_gc;
	ADCB.CH2.MUXCTRL =	ADC_CH_MUXPOS_PIN14_gc;
	ADCB.CH3.MUXCTRL =	ADC_CH_MUXPOS_PIN15_gc;
	
	//initialize conversion complete interrupts on all ADCA channel inputs
	ADCB.CH0.INTCTRL =	ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;
	ADCB.CH1.INTCTRL =	ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;
	ADCB.CH2.INTCTRL =	ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;
	ADCB.CH3.INTCTRL =	ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;
	
	ADCB.EVCTRL =		ADC_SWEEP_0123_gc;
	
	//enable ADCB
	ADCB.CTRLA =		ADC_ENABLE_bm	|
						ADC_CH0START_bm	|
						ADC_CH1START_bm	|
						ADC_CH2START_bm	|
						ADC_CH3START_bm	;

	PMIC.CTRL |= PMIC_LOLVLEN_bm | PMIC_RREN_bm;
}

uint16_t filterData(int16_t *data)
{
	int32_t sum = 0;
	uint8_t inc;
	
	for(inc=0;inc<16;inc++)
	{
		sum+=data[inc];
	}
	
	if	(sum < 0) return 0;
	else
	{
		sum = sum>>3;	
		return (uint16_t) sum;
	}
}

uint16_t analogRead(uint8_t pinNum)
{
	if (pinNum > 7) return 0;
	else			return filterData(&adc_data[pinNum][0]);
}


ISR(ADCA_CH0_vect)
{
	adc_data[0][adcCnt[0].CNT++] = ADCA.CH0.RES;
}
ISR(ADCA_CH1_vect)
{
	adc_data[1][adcCnt[1].CNT++] = ADCA.CH1.RES;
}
ISR(ADCA_CH2_vect)
{
	adc_data[2][adcCnt[2].CNT++] = ADCA.CH2.RES;
}
ISR(ADCA_CH3_vect)
{
	adc_data[3][adcCnt[3].CNT++] = ADCA.CH3.RES;
}



ISR(ADCB_CH0_vect)
{
	adc_data[4][adcCnt[4].CNT++] = ADCB.CH0.RES;
}
ISR(ADCB_CH1_vect)
{
	adc_data[5][adcCnt[5].CNT++] = ADCB.CH1.RES;
}
ISR(ADCB_CH2_vect)
{
	adc_data[6][adcCnt[6].CNT++] = ADCB.CH2.RES;
}
ISR(ADCB_CH3_vect)
{
	adc_data[7][adcCnt[7].CNT++] = ADCB.CH3.RES;
}
