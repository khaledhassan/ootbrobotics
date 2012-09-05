/*
 * TWI.h
 *
 * Created: 7/3/2012 11:09:31 AM
 *  Author: tmartin
 */ 


#ifndef TWI_H_
#define TWI_H_

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <avr/io.h>
#include <avr/interrupt.h>  
#include <util/delay.h>


//#define calcTWMBR(b) ((F_CPU/(2*b))-5)

typedef enum{
	repStart	 = 0,
	receiveData  = 1
	}twiReadSate_t;

twiReadSate_t twiReadSate;

typedef struct{
	uint8_t	chipAddr;			//address that pertains to the IC
	uint8_t	*chipRegAddr;		//poiter to the chips register address.  this cuold be multiple bytes...hence the array
	uint8_t	chipRegAddrLength;	//length (bytes) of chip register address
	uint8_t	*data;				//data to be read or written across the bus
	uint8_t	dataLength;			//length (bytes) of data
	uint8_t	chipRegAddrCount;
	uint8_t	dataCount;
	uint8_t	readState;
}i2cDevice_t;

typedef struct{
	TWI_t					*bus;				//twi bus the IC is on
	i2cDevice_t				*device;				//this is the device currently pointed to on the bus	
}i2cBus_t;


void twiInit(TWI_t *twi,double baud);
void twiInitiateTransfer(i2cBus_t *genBus, uint8_t read);
void twiWriteHandler();
void twiReadHandler();
void twiInterruptHandler(i2cBus_t *genBus);


uint8_t mcp23017RegAddr;
uint8_t mcp23017RegDataBuffer;

//device object definition
i2cDevice_t mcp23017;
i2cBus_t	TWIC_bus;


#endif /* TWI_H_ */

