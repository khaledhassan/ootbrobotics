/*
 * SPI.c
 *
 * Created: 5/21/2012 4:37:41 PM
 *  Author: tmartin
 */ 

#include "SPI.h"

void spiInit(SPI_t *spi,PORT_t *port ,uint8_t mode){
	
	port->DIRSET = 0xB0;	//set directions assuming master opperation

	mode &= (3<<2);				//mode should only have data in the correct bit field
	
	spi->CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | (mode) | SPI_PRESCALER_DIV4_gc ;	//initialize the SPI module
	spi->INTCTRL |= SPI_INTLVL_MED_gc;	//enable mid level int for SPI
	PMIC.CTRL |= PMIC_MEDLVLEN_bm;		//if the mid level interrupt is not enabled do so
}

uint8_t spiRead(SPI_t *spi, uint8_t *data){
	*data = spi->DATA;
}

void spi_Send(SPI_t *spi,uint8_t data){
	while(spi->STATUS & SPI_IF_bm);
	spi->DATA = data;
}

ISR(SPIC_INT_vect){
	spiRead(&SPIC,&spiData);
}
