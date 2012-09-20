/*
 * dac.c
 *
 * Created: 8/2/2012 12:32:30 AM
 *  Author: Tim
 */ 

void dacA0Init()
{
	DACA.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;
	DACA.CTRLB = DAC_CHSEL_DUAL_gc;
	DACA.CTRLC = DAC_REFSEL_INT1V_gc;
}
