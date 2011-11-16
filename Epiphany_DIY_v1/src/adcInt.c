/*
 * adcInt.c
 *
 * Created: 10/29/2011 9:25:47 PM
 *  Author: bfc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>



enum ADC_INTERNAL_SOURCES{
		 TEMP		= 0x00,
		 DANDGAP	= 0x01,	
		 SCALEDVCC	= 0x02,
		 DAC		= 0x03
	};//for external just use the pin number s0-7

#define maxFilterSize	16
#define runningFilterSize	10

#if (runningFilterSize > maxFilterSize)
runningFilterSize = maxFilterSize;
#endif

struct ADC_DATA{
	struct PIN 
	{
		//protected don't mess with these unless you have a good reason
		union DATA{
			uint16_t	rawData;
			uint16_t	dataArray[runningFilterSize];
		};
		//public
		uint16_t dataFiltered;
	}inputPin[8],internalSource[4];
	struct CHANNEL{
		uint8_t source;	// This is used to determine what pin the ADC channel is pointing to
	}CH0,CH1,CH2,CH3;
}ADC_A,ADC_B;


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
	
	ADC_A.CH0.source = 0;
	ADC_A.CH1.source = 1;
	ADC_A.CH2.source = 2;
	ADC_A.CH3.source = 3;
	 
}

ISR(ADCA_CH0_vect){	
}
ISR(ADCA_CH1_vect){
}
ISR(ADCA_CH2_vect){
}
ISR(ADCA_CH3_vect){
}

