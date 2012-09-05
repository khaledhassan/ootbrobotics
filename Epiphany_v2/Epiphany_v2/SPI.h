/*
 * SPI.h
 *
 * Created: 5/21/2012 4:41:06 PM
 *  Author: tmartin
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>


#define SPI_MODE_RISING_SAMPLE	SPI_MODE_0_gc
#define SPI_MODE_RISING_SETUP	SPI_MODE_1_gc
#define SPI_MODE_FALLING_SAMPLE	SPI_MODE_2_gc
#define SPI_MODE_FALLING_SETUP	SPI_MODE_3_gc



void spiInit(SPI_t *spi,PORT_t *port,uint8_t mode);
uint8_t spiRead(SPI_t *spi, uint8_t *data);
void spi_Send(SPI_t *spi,uint8_t data);

volatile uint8_t spiData;


#endif /* SPI_H_ */