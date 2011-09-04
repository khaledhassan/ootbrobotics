/*
 * ADC.h
 *
 * Created: 9/4/2011 12:54:06 AM
 *  Author: Tim
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <asf.h>


#define Internal_Temp			0x80	//internal temperature sensor
#define Internal_BandGap		0x81	//internal band gap voltage use this for calibrations
#define Internal_VccScaled		0x82	//internal vcc/10
#define Internal_DAC			0x83	//way of measuring the DAC output
#define	ADC_InternalChannel_msk	0x80	//Used to detect internal vs external in code

#define ExternalChannel0	0
#define ExternalChannel1	1
#define ExternalChannel2	2
#define ExternalChannel3	3
#define ExternalChannel4	4
#define ExternalChannel5	5
#define ExternalChannel6	6
#define ExternalChannel7	7

#define ADCA_CH0_ConvComplete	(ADCA.CH0.INTFLAGS & ADC_CH_CHIF_bm)	//determines if the conversion has been completed
#define ADCA_CH1_ConvComplete	(ADCA.CH1.INTFLAGS & ADC_CH_CHIF_bm)	//determines if the conversion has been completed
#define ADCA_CH2_ConvComplete	(ADCA.CH2.INTFLAGS & ADC_CH_CHIF_bm)	//determines if the conversion has been completed
#define ADCA_CH3_ConvComplete	(ADCA.CH3.INTFLAGS & ADC_CH_CHIF_bm)	//determines if the conversion has been completed

#define ADCB_CH0_ConvComplete	(ADCA.CH0.INTFLAGS & ADC_CH_CHIF_bm)	//determines if the conversion has been completed
#define ADCB_CH1_ConvComplete	(ADCA.CH1.INTFLAGS & ADC_CH_CHIF_bm)	//determines if the conversion has been completed
#define ADCB_CH2_ConvComplete	(ADCA.CH2.INTFLAGS & ADC_CH_CHIF_bm)	//determines if the conversion has been completed
#define ADCB_CH3_ConvComplete	(ADCA.CH3.INTFLAGS & ADC_CH_CHIF_bm)	//determines if the conversion has been completed



void ADCsInits(void);//initializes the ADC modules		
void ADCA_request(uint8_t ADCChannel,uint8_t inputChannel);	//get data from any of the 8 external channels or the 4 internal channels.  Example choose ExternalChannel0..7 or any of the 4 Internal_... channels.
void ADCB_request(uint8_t ADCChannel,uint8_t inputChannel);	//get data from any of the 8 external channels or the 4 internal channels.  Example choose ExternalChannel0..7 or any of the 4 Internal_... channels.

uint16_t ADCA_getVal(uint8_t ADCChannel);//returns the last chn conversion. 0xFFFF means an error occurred 
uint16_t ADCB_getVal(uint8_t ADCChannel);//returns the last chn conversion. 0xFFFF means an error occurred 

#endif /* ADC_H_ */