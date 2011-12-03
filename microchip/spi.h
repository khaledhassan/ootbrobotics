#ifndef SPI_H_
#define SPI_H_

#define spiConflictFlag (SSP1CON1 & 0x80)

/*
 * initialization routine for the spi module
*/
void spiInit();
/*
 * function is used to send a charater through the spi module
*/
void spi_putC(char c);
/*
	enables the spi interface
*/
void spiEnable();
/*
	disables the spi interface.  This allows use of rck which shares
	the same pin as RCK.  since spi input is not utilized there is no conflict.
*/
void spiDisable();

void sendServoStartSignal();

#endif