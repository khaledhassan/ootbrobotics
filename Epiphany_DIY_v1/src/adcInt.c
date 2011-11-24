/*
 * adcInt.c
 *
 * Created: 10/29/2011 9:25:47 PM
 *  Author: bfc
 */ 
#include "adcInt.h"		


void adcAInit(){
	
	//ADCA.CTRLA = ADC_DMASEL_CH0123_gc;		//set up dma on all channels
	
	ADCA.CTRLB = ADC_RESOLUTION_12BIT_gc | ADC_FREERUN_bm;		//12 bit mode right adjusted and free running
	ADCA.REFCTRL = ADC_REFSEL_VCC_gc;			//VCC/1.6 selected as Vref. if 3.3 = vcc. ref = 2.0625V
	ADCA.PRESCALER = ADC_PRESCALER_DIV16_gc;	//32MHz / 16 = 2MHz which is the ADC max speed
	
	ADCA.CH0.INTCTRL = ADC_CH_INTLVL_LO_gc;	
	ADCA.CH1.INTCTRL = ADC_CH_INTLVL_LO_gc;
	ADCA.CH2.INTCTRL = ADC_CH_INTLVL_LO_gc;
	ADCA.CH3.INTCTRL = ADC_CH_INTLVL_LO_gc;
	
	ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	
	PMIC.CTRL |= PMIC_LOLVLEN_bm;				//make sure low level interrupts are enabled
	
	ADCA.CH0.MUXCTRL = 
}

ISR(ADCA_CH0_vect){	
	switch()
}
ISR(ADCA_CH1_vect){
}
ISR(ADCA_CH2_vect){
}
ISR(ADCA_CH3_vect){
}

