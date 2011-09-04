/*
 * ADC.c
 *
 * Created: 9/4/2011 12:53:48 AM
 *  Author: Tim
 */ 
	#include "ADC.h"

void ADCA_request(uint8_t ADCChannel,uint8_t inputChannel){
	//internal signal to be measured?
	if (inputChannel & ADC_InternalChannel_msk){
		inputChannel &= 0x0F;
		
		switch(ADCChannel){
		case(0):
		ADCA.CH0.MUXCTRL = inputChannel<<3;
		ADCA.CH0.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		break;
		case(1):
		ADCA.CH1.MUXCTRL = inputChannel<<3;
		ADCA.CH1.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		break;
		case(2):
		ADCA.CH2.MUXCTRL = inputChannel<<3;
		ADCA.CH2.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		break;
		case(3):
		ADCA.CH3.MUXCTRL = inputChannel<<3;
		ADCA.CH3.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		break;
		default:
		ADCA.CH0.MUXCTRL = inputChannel<<3;
		ADCA.CH0.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		}		
	}
	else{
		switch(ADCChannel){
		case(0):
		ADCA.CH0.MUXCTRL = inputChannel<<3;
		ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		break;
		case(1):
		ADCA.CH1.MUXCTRL = inputChannel<<3;
		ADCA.CH1.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		break;
		case(2):
		ADCA.CH2.MUXCTRL = inputChannel<<3;
		ADCA.CH2.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		break;
		case(3):
		ADCA.CH3.MUXCTRL = inputChannel<<3;
		ADCA.CH3.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		break;
		default:
		ADCA.CH0.MUXCTRL = inputChannel<<3;
		ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		}
	}
}


void ADCB_request(uint8_t ADCChannel,uint8_t inputChannel){
	//internal signal to be measured?
	if (inputChannel & ADC_InternalChannel_msk){
		inputChannel &= 0x0F;
		
		switch(ADCChannel){
		case(0):
		ADCB.CH0.MUXCTRL = inputChannel<<3;
		ADCB.CH0.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		break;
		case(1):
		ADCB.CH1.MUXCTRL = inputChannel<<3;
		ADCB.CH1.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		break;
		case(2):
		ADCB.CH2.MUXCTRL = inputChannel<<3;
		ADCB.CH2.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		break;
		case(3):
		ADCB.CH3.MUXCTRL = inputChannel<<3;
		ADCB.CH3.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		break;
		default:
		ADCB.CH0.MUXCTRL = inputChannel<<3;
		ADCB.CH0.CTRL = ADC_CH_INPUTMODE_INTERNAL_gc | ADC_CH_START_bm;
		}		
	}
	else{
		switch(ADCChannel){
		case(0):
		ADCB.CH0.MUXCTRL = inputChannel<<3;
		ADCB.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		break;
		case(1):
		ADCB.CH1.MUXCTRL = inputChannel<<3;
		ADCB.CH1.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		break;
		case(2):
		ADCB.CH2.MUXCTRL = inputChannel<<3;
		ADCB.CH2.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		break;
		case(3):
		ADCB.CH3.MUXCTRL = inputChannel<<3;
		ADCB.CH3.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		break;
		default:
		ADCB.CH0.MUXCTRL = inputChannel<<3;
		ADCB.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc | ADC_CH_START_bm;
		}
	}
}


uint16_t ADCA_getVal(uint8_t ADCChannel){
	uint8_t attempts = 0;
	switch(ADCChannel){
		case(0):
			while(!ADCA_CH0_ConvComplete){
				attempts++;
				if(attempts > 4)return 0xFFFF;
			}
			ADCA_CH0_INTFLAGS = ADC_CH_CHIF_bm;//clear bit by writing a one to it
			return ADCA_CH0RES;
		break;
		case(1):
			while(!ADCA_CH1_ConvComplete){
				attempts++;
				if(attempts > 4)return 0xFFFF;
			}
			ADCA_CH1_INTFLAGS = ADC_CH_CHIF_bm;//clear bit by writing a one to it
			return ADCA_CH1RES;
		break;
		case(2):
			while(!ADCA_CH2_ConvComplete){
				attempts++;
				if(attempts > 4)return 0xFFFF;
			}
			ADCA_CH2_INTFLAGS = ADC_CH_CHIF_bm;//clear bit by writing a one to it
			return ADCA_CH2RES;
		break;
		case(3):
			while(!ADCA_CH3_ConvComplete){
				attempts++;
				if(attempts > 4)return 0xFFFF;
			}
			ADCA_CH3_INTFLAGS = ADC_CH_CHIF_bm;//clear bit by writing a one to it
			return ADCA_CH3RES;
		break;
		default:
			return 0xFFFF;
		break;
	}
}

uint16_t ADCB_getVal(uint8_t ADCChannel){
	uint8_t attempts = 0;
	switch(ADCChannel){
		case(0):
			while(!ADCB_CH0_ConvComplete){
				attempts++;
				if(attempts > 4)return 0xFFFF;
			}
			ADCB_CH0_INTFLAGS = ADC_CH_CHIF_bm;//clear bit by writing a one to it
			return ADCB_CH0RES;
		break;
		case(1):
			while(!ADCB_CH1_ConvComplete){
				attempts++;
				if(attempts > 4)return 0xFFFF;
			}
			ADCB_CH1_INTFLAGS = ADC_CH_CHIF_bm;//clear bit by writing a one to it
			return ADCB_CH1RES;
		break;
		case(2):
			while(!ADCB_CH2_ConvComplete){
				attempts++;
				if(attempts > 4)return 0xFFFF;
			}
			ADCB_CH2_INTFLAGS = ADC_CH_CHIF_bm;//clear bit by writing a one to it
			return ADCB_CH2RES;
		break;
		case(3):
			while(!ADCB_CH3_ConvComplete){
				attempts++;
				if(attempts > 4)return 0xFFFF;
			}
			ADCB_CH3_INTFLAGS = ADC_CH_CHIF_bm;//clear bit by writing a one to it
			return ADCB_CH3RES;
		break;
		default:
			return 0xFFFF;
		break;
	}
}



void ADCsInits(void){
	ADCA.CTRLA |= ADC_ENABLE_bm;//enable ADCs
	ADCB.CTRLA |= ADC_ENABLE_bm;
	
	ADCA.REFCTRL = ADC_REFSEL_VCC_gc | ADC_BANDGAP_bm | ADC_TEMPREF_bm; //ref of 2.0625.  Due to external circuitry the ref is 5V for the 8 channels that support it.  To get the full 5V range make sure the 5V/3.3V jumper above the ADC is jumpered towards 5V.  Otherwise signals will be truncated at 5V.
	ADCB.REFCTRL = ADC_REFSEL_VCC_gc | ADC_BANDGAP_bm | ADC_TEMPREF_bm; //also bandgap and temp referenaces are initialized.
	
	ADCA.PRESCALER = ADC_PRESCALER_DIV32_gc;//setup for max of 1MHz limited by op-amps
	ADCB.PRESCALER = ADC_PRESCALER_DIV32_gc;

/*	ADCA.CH0.INTCTRL = ADC_CH_INTLVL_LO_gc | ADC_CH_INTMODE_COMPLETE_gc;
	ADCA.CH1.INTCTRL = ADC_CH_INTLVL_LO_gc | ADC_CH_INTMODE_COMPLETE_gc;
	ADCA.CH2.INTCTRL = ADC_CH_INTLVL_LO_gc | ADC_CH_INTMODE_COMPLETE_gc;
	ADCA.CH3.INTCTRL = ADC_CH_INTLVL_LO_gc | ADC_CH_INTMODE_COMPLETE_gc;

	ADCB.CH0.INTCTRL = ADC_CH_INTLVL_LO_gc | ADC_CH_INTMODE_COMPLETE_gc;
	ADCB.CH1.INTCTRL = ADC_CH_INTLVL_LO_gc | ADC_CH_INTMODE_COMPLETE_gc;
	ADCB.CH2.INTCTRL = ADC_CH_INTLVL_LO_gc | ADC_CH_INTMODE_COMPLETE_gc;
	ADCB.CH3.INTCTRL = ADC_CH_INTLVL_LO_gc | ADC_CH_INTMODE_COMPLETE_gc;
	
	PMIC.CTRL |= PMIC_LOLVLEN_bm;*/
}

