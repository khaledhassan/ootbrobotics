/*
 * utility.c
 *
 * Created: 8/27/2013 7:17:48 PM
 *  Author: Tim
 */ 

#include "utility.h"

uint8_t ReadCalibrationByte( uint8_t index )
{
	uint8_t result;

	/* Load the NVM Command register to read the calibration row. */
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
	result = pgm_read_byte(index);

	/* Clean up NVM Command register. */
	NVM_CMD = NVM_CMD_NO_OPERATION_gc;

	return( result );
}