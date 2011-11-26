/*
 * servoControllerATtiny4313.asm
 *
 *  Created: 11/6/2011 4:03:32 PM
 *   Author: bfc
 */

	
.INCLUDE	"servoControlDefs.asm"

.CSEG
	
.ORG	0x0	
RESET:	rjmp	setup					

.ORG	0x0004	
		rjmp	TIMER1_COMPA_vect	
.ORG	0x0007
		rjmp	USART0_RX_vect			
.ORG	0x000C
		rjmp	TIMER1_COMPB_vect	
				
		;place initializations here
setup:
		RCALL	uartInit
		RCALL	setMasksCall
		RCALL	seedValuesCall
		RCALL	refreshCall
		RCALL	sort
		RCALL	seedTimerCompares
		RCALL	timer1Init
		SEI					;enable global interrupts


main:						;this is where the main code is put
		rjmp	main

;sub routines
uartInit:
		CLR		r16
		STS		0x22,r16
		LDI		r16,2		
		STS		0x29,r16
		LDI		r16,(1<<RXCIE | 1<<RXEN)
		STS		0x2A,r16			
		RET
setMasksCall:
.INCLUDE    "setMasks.asm"

seedValuesCall:
.INCLUDE    "seedValues.asm"
		
refreshCall:
.INCLUDE    "refresh.asm"
		
sort:
		RET
seedTimerCompares:
		//set compareA initial state
		LDS		r16,(timerval + 0)
		STS		0x4A,r16
		
		LDS		r16,(timerval + 1)
		STS		0x4B,r16

		//set compareB initial state		
		LDS		r16,(timerval + 0)
		STS		0x48,r16
		
		LDS		r16,(timerval + 1)
		STS		0x49,r16
						
		RET
timer1Init:
		LDI		r16,0	
		STS		0x4F,r16
		LDI		r16,0x1A;; //sets ICR1 as top val reg and sets the prescaler to div8 enables ctc for immediate updates to ocr1x
		STS		0x4E,r16
		LDI		r16,( 1<<OCIE1A | 1<<OCIE1A ) 
		STS		TIMSK,r16
		LDI		r16,LOW(30000) 
		STS		ICR1L,r16
		LDI		r16,HIGH(30000) 
		STS		ICR1H,r16
		RET		
;interrupts



TIMER1_COMPA_vect:	
		RETI
TIMER1_COMPB_vect:
		RETI
USART0_RX_vect:
		RETI