#include <htc.h>
#include "spi.h"

void spiInit(){
    //spi config
    SSP1CON1 = 0x10; //spi set baud and master
//	SSP1STAT |= 0x40;
    SSP1CON1 |= 0x20; //spi enable
}

void spi_putC(char c){
    SSP1BUF = c;
}

void spiEnable()
{
	SSP1CON1 |= 0x20; // enable spi
}

void spiDisable()
{
	SSP1CON1 &= ~0x20;	//disable spi
}

void sendServoStartSignal(){
	LATC = 0x20;
	do{
	SSP1CON1  &= 0x7F;
	SSP1BUF = 0xFF;
	}while(spiConflictFlag);
	do{
	SSP1CON1  &= 0x7F;
	SSP1BUF = 0xFF;
	}while(spiConflictFlag);
	do{
	SSP1CON1  &= 0x7F;
	SSP1BUF = 0xFF;
	}while(spiConflictFlag);
	LATC = 0x22;	
}
