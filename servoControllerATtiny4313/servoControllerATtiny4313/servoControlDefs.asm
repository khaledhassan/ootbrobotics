/*
 * servoControlDefs.asm
 *
 *  Created: 11/7/2011 12:13:08 AM
 *   Author: bfc
 */ 

 .SET	seedMultiplier	= 5
.SET	div				= 8
.SET	F_CPU			= 8000000
.SET	timerPeriod		= (F_CPU/50/div)	;resolution of the timer	  
	
.INCLUDE	"tn4313def.inc"
.DSEG

servoBufferRegs:	.byte	48; buffered data for the servo timerval
timerval:			.byte	48; holds timing data for the servo  
mask:				.byte	24; mask repective to the servo port	
currentServo		.byte	1;	the servo being refferenced currently

timervalTemp		.byte	2;
maskTemp			.byte	1;
.ESEG

servoTypes:			.byte	24