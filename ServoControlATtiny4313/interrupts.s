/*
 * interrupts.asm
 *
 * Created: 11/12/2011 12:53:13 AM
 *  Author: bfc
 */ 
#define _SFR_ASM_COMPAT 1
#define __SFR_OFFSET 0

 //ISR(TIMER1_COMPA_vect){
 /*
 20c:	1f 92       	push	r1
 20e:	0f 92       	push	r0
 210:	0f b6       	in	r0, 0x3f	; 63
 212:	0f 92       	push	r0
 214:	11 24       	eor	r1, r1
 216:	2f 93       	push	r18
 218:	8f 93       	push	r24
 21a:	9f 93       	push	r25
 21c:	ef 93       	push	r30
 21e:	ff 93       	push	r31
 */
.ORG	0000020c
//OCR1A = servo[currentServo + 2].TimerVal;	
						lds	r30, 0x0061
						ldi	r31, 0x00	; 0
						add	r30, r30
						adc	r31, r31
						add	r30, r30
						adc	r31, r31
						subi	r30, 0x52	; 82
						sbci	r31, 0xFF	; 255
						ld	r24, Z
						ldd	r25, Z+1	; 0x01
						out	0x2b, r25	; 43
						out	0x2a, r24	; 42
//	PORTD = DECODE0 | DECODE1 | DECODE2;
						ldi	r24, 0xE0	; 224
						out	0x12, r24	; 18
//	if((servo[currentServo].mask & 0xC000) == 0xC000){
						lds	r30, 0x0061
						ldi	r31, 0x00	; 0
						add	r30, r30
						adc	r31, r31
						add	r30, r30
						adc	r31, r31
						subi	r30, 0x5A	; 90
						sbci	r31, 0xFF	; 255
						ldd	r24, Z+2	; 0x02
						ldd	r25, Z+3	; 0x03
						andi	r24, 0x00	; 0
						andi	r25, 0xC0	; 192
						ldi	r18, 0xC0	; 192
						cpi	r24, 0x00	; 0
						cpc	r25, r18
						brne	.+38     	; 0x286 <__vector_4+0x7a>
//			servoBus[0] = PORTA = *(&servo[currentServo].TimerVal+1) | servoBus[0]; 	
						lds	r30, 0x0061
						lds	r24, 0x0106
						ldi	r31, 0x00	; 0
						add	r30, r30
						adc	r31, r31
						add	r30, r30
						adc	r31, r31
						subi	r30, 0x58	; 88
						sbci	r31, 0xFF	; 255
						ld	r25, Z
						or	r24, r25
						out	0x1b, r24	; 27
						in	r24, 0x1b	; 27
						sts	0x0106, r24
//			PORTD = DECODE1 | DECODE2;
						ldi	r24, 0xC0	; 192
						rjmp	.+142    	; 0x314 <__vector_4+0x108>
//	}			
//	else if((servo[currentServo].mask & 0xA000) == 0xA000){
						lds	r30, 0x0061
						ldi	r31, 0x00	; 0
						add	r30, r30
						adc	r31, r31
						add	r30, r30
						adc	r31, r31
						subi	r30, 0x5A	; 90
						sbci	r31, 0xFF	; 255
						ldd	r24, Z+2	; 0x02
						ldd	r25, Z+3	; 0x03
						andi	r24, 0x00	; 0
						andi	r25, 0xA0	; 160
						ldi	r18, 0xA0	; 160
						cpi	r24, 0x00	; 0
						cpc	r25, r18
						brne	.+38     	; 0x2ce <__vector_4+0xc2>
//			servoBus[1] = PORTA = *(&servo[currentServo].TimerVal+1) | servoBus[1]; 	
						lds	r30, 0x0061
						lds	r24, 0x0107
						ldi	r31, 0x00	; 0
						add	r30, r30
						adc	r31, r31
						add	r30, r30
						adc	r31, r31
						subi	r30, 0x58	; 88
						sbci	r31, 0xFF	; 255
						ld	r25, Z
						or	r24, r25
						out	0x1b, r24	; 27
						in	r24, 0x1b	; 27
						sts	0x0107, r24
//			PORTD = DECODE0 | DECODE2;
						ldi	r24, 0xA0	; 160
						rjmp	.+70     	; 0x314 <__vector_4+0x108>
//	}
	else if((servo[currentServo].mask & 0x6000) == 0x6000){	
						lds	r30, 0x0061
						ldi	r31, 0x00	; 0
						add	r30, r30
						adc	r31, r31
						add	r30, r30
						adc	r31, r31
						subi	r30, 0x5A	; 90
						sbci	r31, 0xFF	; 255
						ldd	r24, Z+2	; 0x02
						ldd	r25, Z+3	; 0x03
						andi	r24, 0x00	; 0
						andi	r25, 0x60	; 96
						ldi	r18, 0x60	; 96
						cpi	r24, 0x00	; 0
						cpc	r25, r18
						brne	.+38     	; 0x316 <__vector_4+0x10a>
//			servoBus[2] = PORTA = *(&servo[currentServo].TimerVal+1) | servoBus[2]; 	
						lds	r30, 0x0061
						lds	r24, 0x0108
						ldi	r31, 0x00	; 0
						add	r30, r30
						adc	r31, r31
						add	r30, r30
						adc	r31, r31
						subi	r30, 0x58	; 88
						sbci	r31, 0xFF	; 255
						ld	r25, Z
						or	r24, r25
						out	0x1b, r24	; 27
						in	r24, 0x1b	; 27
						sts	0x0108, r24
//			PORTD = DECODE0 | DECODE1;
						ldi	r24, 0x60	; 96
						out	0x12, r24	; 18
//	}		
//	currentServo++;	
						lds	r24, 0x0061
						subi	r24, 0xFF	; 255
						sts	0x0061, r24
//}
/*
 320:	ff 91       	pop	r31
 322:	ef 91       	pop	r30
 324:	9f 91       	pop	r25
 326:	8f 91       	pop	r24
 328:	2f 91       	pop	r18
 32a:	0f 90       	pop	r0
 32c:	0f be       	out	0x3f, r0	; 63
 32e:	0f 90       	pop	r0
 330:	1f 90       	pop	r1
 */
						reti




