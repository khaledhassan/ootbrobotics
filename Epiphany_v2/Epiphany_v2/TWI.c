/*
 * TWI.c
 *
 * Created: 6/20/2012 2:26:25 PM
 *  Author: tmartin
 */ 

#include "TWI.h"

uint8_t mcp23017RegAddr = 0;
uint8_t mcp23017RegDataBuffer = 0;

twiReadSate_t twiReadSate;

//device object definition
i2cDevice_t mcp23017 = {0x20,&mcp23017RegAddr,1,&mcp23017RegDataBuffer,1,0,0};
i2cBus_t	TWIC_bus = {&TWIC,&mcp23017};

void twiInit(TWI_t *twi,double baud){
	//set baud rate for twi aka I2C
	twi->MASTER.BAUD = (F_CPU/(baud*2))-5;
	//enable twi interrupts and set int level as well as enabling the peripheral
	twi->MASTER.CTRLA = TWI_MASTER_INTLVL_MED_gc | TWI_MASTER_RIEN_bm | TWI_MASTER_WIEN_bm | TWI_MASTER_ENABLE_bm;
	//set status to idle
	twi->MASTER.STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
	//enable mid-level interrupts globally
	PMIC.CTRL |= PMIC_MEDLVLEN_bm;
}

void twiInitiateTransfer(i2cBus_t *genBus, uint8_t read)
{	
	//address is shifted to account for the lowest bit read/write
	uint8_t const chipAddr = (genBus->device->chipAddr)<<1;
	
	if(read)
	{
			//send out the chip address with the read command	
			genBus->bus->MASTER.ADDR = chipAddr | 1;
			genBus->device->readState = repStart;
	}			
	else
	{
		//send out the chip address with the write command	
		genBus->bus->MASTER.ADDR = chipAddr;
	}		
}

void twiWriteHandler(i2cBus_t *genBus)
{
	//handler for device register address.  Some ICs may have a address longer than a single byte
	if(genBus->device->chipRegAddrLength > genBus->device->chipRegAddrCount)
	{
		genBus->bus->MASTER.DATA = genBus->device->chipRegAddr[genBus->device->chipRegAddrCount++];	
	}
	//handler for device data transfer
	else if(genBus->device->dataLength > genBus->device->dataCount)
	{
		genBus->bus->MASTER.DATA = genBus->device->data[genBus->device->dataCount++];
	}
	else
	{
		genBus->bus->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
		genBus->device->dataCount = 0;
		genBus->device->chipRegAddrCount = 0;
	}	
	
}

void twiReadHandler(i2cBus_t *genBus){
		if (genBus->device->readState == repStart)
		{
			genBus->bus->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_REPSTART_gc;
			genBus->bus->MASTER.ADDR = (genBus->device->chipAddr<<1) | 1;
			genBus->device->readState = receiveData;			
		}
		else if(genBus->device->dataLength > genBus->device->dataCount)
		{
			genBus->device->data[genBus->device->dataCount++] = genBus->bus->MASTER.DATA ;
		}
		else
		{
			genBus->bus->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
			genBus->device->dataCount = 0;
			genBus->device->chipRegAddrCount = 0;
		}
}

void twiInterruptHandler(i2cBus_t *genBus)
{
	if(genBus->bus->MASTER.STATUS & TWI_MASTER_WIF_bm)
	{
		twiWriteHandler(genBus);
	}
	else if(genBus->bus->MASTER.STATUS & TWI_MASTER_RIF_bm)
	{
		twiReadHandler(genBus);
	}
	//there are other relevant states but right now I do not care
}

ISR(TWIC_TWIM_vect){twiInterruptHandler(&TWIC_bus);}

