/*
 * uart.c
 *
 * Created: 7/7/2011 9:55:17 PM
 *  Author: Tim
 */ 
#include "uart.h"

#define bufferSize	64

struct Buffer{
	const uint8_t *bufferBegin;
	const uint8_t *bufferEnd;
	uint8_t *head;
	uint8_t *tail;
	uint8_t data[bufferSize];
}bufC0
//#ifdef enableUartC1
,bufC1
//#endif
//#ifdef enableUartD0
,bufD0
//#endif
//#ifdef enableUartD1
,bufD1
//#endif
//#ifdef enableUartE0
,bufE0
//#endif
//#ifdef enableUartE1
,bufE1
//#endif
//#ifdef enableUartF0
,bufF0
//#endif
//#ifdef enableUartF1
,bufF1
//#endif
;

//sets up all of the streams

FILE uartC0_str = FDEV_SETUP_STREAM(uartC0_putchar, uartC0_getchar, _FDEV_SETUP_RW);
FILE uartC1_str = FDEV_SETUP_STREAM(uartC1_putchar, uartC1_getchar, _FDEV_SETUP_RW);

FILE uartD0_str = FDEV_SETUP_STREAM(uartD0_putchar, uartD0_getchar, _FDEV_SETUP_RW);
FILE uartD1_str = FDEV_SETUP_STREAM(uartD1_putchar, uartD1_getchar, _FDEV_SETUP_RW);

//FILE uartE0_str = FDEV_SETUP_STREAM(uartE0_putchar, uartE0_getchar, _FDEV_SETUP_RW);
FILE uartE0_str = FDEV_SETUP_STREAM(uartE0_putchar, NULL, _FDEV_SETUP_WRITE);

FILE uartE1_str = FDEV_SETUP_STREAM(uartE1_putchar, uartE1_getchar, _FDEV_SETUP_RW);

FILE uartF0_str = FDEV_SETUP_STREAM(uartF0_putchar, uartF0_getchar, _FDEV_SETUP_RW);
FILE uartF1_str = FDEV_SETUP_STREAM(uartF1_putchar, uartF1_getchar, _FDEV_SETUP_RW);


//these functions are used for outputing data from the uarts

void uartF0_putchar(char c,FILE *unused)
{
	while(!(USARTF0.STATUS & USART_DREIF_bm));
	USARTF0.DATA = c;
}
void uartF1_putchar(char c,FILE *unused)
{
	while(!(USARTF1.STATUS & USART_DREIF_bm));
	USARTF1.DATA = c;
}
void uartE0_putchar(char c,FILE *unused)
{
	while(!(USARTE0.STATUS & USART_DREIF_bm));
	USARTE0.DATA = c;
}
void uartE1_putchar(char c,FILE *unused)
{
	while(!(USARTE1.STATUS & USART_DREIF_bm));
	USARTE1.DATA = c;
}
void uartD0_putchar(char c,FILE *unused)
{
	while(!(USARTD0.STATUS & USART_DREIF_bm));
	USARTD0.DATA = c;
}
void uartD1_putchar(char c,FILE *unused)
{
	while(!(USARTD1.STATUS & USART_DREIF_bm));
	USARTD1.DATA = c;
}
void uartC0_putchar(char c,FILE *unused)
{
	while(!(USARTC0.STATUS & USART_DREIF_bm));
	USARTC0.DATA = c;
}
void uartC1_putchar(char c,FILE *unused)
{
	while(!(USARTC1.STATUS & USART_DREIF_bm));
	USARTC1.DATA = c;
}

int uartC0_getchar(FILE *stream){
	
	if (bufC0.tail == bufC0.bufferEnd){
		uint8_t temp = *bufC0.tail;
		bufC0.tail = bufC0.bufferBegin;
		return temp;
	}
	else return *bufC0.tail++;
}

void storeC0(char c){
	if(bufC0.head == bufC0.bufferEnd){
		*bufC0.head = c;
		bufC0.head = bufC0.bufferBegin;	
	}		
	else *bufC0.head++ = c;
}

uint8_t dataInBufC0(void){
	if(bufC0.head == bufC0.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
ISR(USARTC0_RXC_vect){
	storeC0(USARTC0.DATA);
}

#ifdef enableUartC1

int uartC1_getchar(FILE *stream){
	
	if (bufC1.tail == bufC1.bufferEnd){
		uint8_t temp = *bufC1.tail;
		bufC1.tail = bufC1.bufferBegin;
		return temp;
	}
	else return *bufC1.tail++;
}

void storeC1(char c){
	if(bufC1.head == bufC1.bufferEnd){
		*bufC1.head = c;
		bufC1.head = bufC1.bufferBegin;	
	}		
	else *bufC1.head++ = c;
}

uint8_t dataInBufC1(void){
	if(bufC1.head == bufC1.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
ISR(USARTC1_RXC_vect){
	storeC1(USARTC1.DATA);
}

#endif

#ifdef enableUartD0

int uartD0_getchar(FILE *stream){
	
	if (bufD0.tail == bufD0.bufferEnd){
		uint8_t temp = *bufD0.tail;
		bufD0.tail = bufD0.bufferBegin;
		return temp;
	}
	else return *bufD0.tail++;
}

void storeD0(char c){
	if(bufD0.head == bufD0.bufferEnd){
		*bufD0.head = c;
		bufD0.head = bufD0.bufferBegin;	
	}		
	else *bufD0.head++ = c;
}

uint8_t dataInBufD0(void){
	if(bufD0.head == bufD0.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
ISR(USARTD0_RXC_vect){
	storeD0(USARTD0.DATA);
}

#endif

#ifdef enableUartD1

int uartD1_getchar(FILE *stream){
	
	if (bufD1.tail == bufD1.bufferEnd){
		uint8_t temp = *bufD1.tail;
		bufD1.tail = bufD1.bufferBegin;
		return temp;
	}
	else return *bufD1.tail++;
}

void storeD1(char c){
	if(bufD1.head == bufD1.bufferEnd){
		*bufD1.head = c;
		bufD1.head = bufD1.bufferBegin;	
	}		
	else *bufD1.head++ = c;
}

uint8_t dataInBufD1(void){
	if(bufD1.head == bufD1.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
ISR(USARTD1_RXC_vect){
	storeD1(USARTD1.DATA);
}

#endif

#ifdef enableUartE0

int uartE0_getchar(FILE *stream){
	
	if (bufE0.tail == bufE0.bufferEnd){
		uint8_t temp = *bufE0.tail;
		bufE0.tail = bufE0.bufferBegin;
		return temp;
	}
	else return *bufE0.tail++;
}

void storeE0(char c){
	if(bufE0.head == bufE0.bufferEnd){
		*bufE0.head = c;
		bufE0.head = bufE0.bufferBegin;	
	}		
	else *bufE0.head++ = c;
}

uint8_t dataInBufE0(void){
	if(bufE0.head == bufE0.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
/*
ISR(USARTE0_RXC_vect){
	storeE0(USARTE0.DATA);
}
*/
#endif

#ifdef enableUartE1

int uartE1_getchar(FILE *stream){
	
	if (bufE1.tail == bufE1.bufferEnd){
		uint8_t temp = *bufE1.tail;
		bufE1.tail = bufE1.bufferBegin;
		return temp;
	}
	else return *bufE1.tail++;
}

void storeE1(char c){
	if(bufE1.head == bufE1.bufferEnd){
		*bufE1.head = c;
		bufE1.head = bufE1.bufferBegin;	
	}		
	else *bufE1.head++ = c;
}

uint8_t dataInBufE1(void){
	if(bufE1.head == bufE1.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
ISR(USARTE1_RXC_vect){
	storeE1(USARTE1.DATA);
}

#endif

#ifdef enableUartF0

int uartF0_getchar(FILE *stream){
	
	if (bufF0.tail == bufF0.bufferEnd){
		uint8_t temp = *bufF0.tail;
		bufF0.tail = bufF0.bufferBegin;
		return temp;
	}
	else return *bufF0.tail++;
}

void storeF0(char c){
	if(bufF0.head == bufF0.bufferEnd){
		*bufF0.head = c;
		bufF0.head = bufF0.bufferBegin;	
	}		
	else *bufF0.head++ = c;
}

uint8_t dataInBufF0(void){
	if(bufF0.head == bufF0.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
ISR(USARTF0_RXC_vect){
	storeF0(USARTF0.DATA);
}

#endif

#ifdef enableUartF0

int uartF1_getchar(FILE *stream){
	
	if (bufF1.tail == bufF1.bufferEnd){
		uint8_t temp = *bufF1.tail;
		bufF1.tail = bufF1.bufferBegin;
		return temp;
	}
	else return *bufF1.tail++;
}

void storeF1(char c){
	if(bufF1.head == bufF1.bufferEnd){
		*bufF1.head = c;
		bufF1.head = bufF1.bufferBegin;	
	}		
	else *bufF1.head++ = c;
}

uint8_t dataInBufF1(void){
	if(bufF1.head == bufF1.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
ISR(USARTF1_RXC_vect){
	storeF1(USARTF1.DATA);
}

#endif

//initialization functions for the uarts
void uartInit(USART_t *uart, long baud)
{
	PMIC.CTRL |= PMIC_MEDLVLEX_bm;
	if (uart == &USARTC0) {
		PORTC.DIRSET = 0x8;
		bufC0.bufferEnd = &bufC0.data[bufferSize-1];	
		bufC0.bufferBegin = &bufC0.data[0];
		bufC0.head = bufC0.bufferBegin;
		bufC0.tail = bufC0.bufferBegin;
		asm("nop");
	}
	else if (uart == &USARTC1){
		PORTC.DIRSET = 0x80;
		PORTC.DIRSET = 0x8;
		bufC1.bufferEnd = &bufC1.data[bufferSize-1];	
		bufC1.bufferBegin = &bufC1.data[0];
		bufC1.head = bufC1.bufferBegin;
		bufC1.tail = bufC1.bufferBegin;
	}			
	else if (uart == &USARTD0) {
		PORTD.DIRSET = 0x8;	
		PORTC.DIRSET = 0x8;
		bufD0.bufferEnd = &bufD0.data[bufferSize-1];	
		bufD0.bufferBegin = &bufD0.data[0];
		bufD0.head = bufD0.bufferBegin;
		bufD0.tail = bufD0.bufferBegin;
	}		
	else if (uart == &USARTD1) {
		PORTD.DIRSET = 0x80;
		PORTC.DIRSET = 0x8;
		bufD1.bufferEnd = &bufD1.data[bufferSize-1];	
		bufD1.bufferBegin = &bufD1.data[0];
		bufD1.head = bufD1.bufferBegin;
		bufD1.tail = bufD1.bufferBegin;	
	}		
	else if (uart == &USARTE0) {
		PORTE.DIRSET = 0x8;
		PORTC.DIRSET = 0x8;
		bufE0.bufferEnd = &bufE0.data[bufferSize-1];	
		bufE0.bufferBegin = &bufE0.data[0];
		bufE0.head = bufE0.bufferBegin;
		bufE0.tail = bufE0.bufferBegin;
	}			
	else if (uart == &USARTE1) {
		PORTE.DIRSET = 0x80;	
		bufE1.bufferEnd = &bufE1.data[bufferSize-1];	
		bufE1.bufferBegin = &bufE1.data[0];
		bufE1.head = bufE1.bufferBegin;
		bufE1.tail = bufE1.bufferBegin;
		asm("nop");

	}	
	else if (uart == &USARTF0) {
		PORTF.DIRSET = 0x8;
		PORTC.DIRSET = 0x8;
		bufF0.bufferEnd = &bufF0.data[bufferSize-1];	
		bufF0.bufferBegin = &bufF0.data[0];
		bufF0.head = bufF0.bufferBegin;
		bufF0.tail = bufF0.bufferBegin;	
	}		
	else if (uart == &USARTF1) {
		PORTF.DIRSET = 0x80;
		PORTC.DIRSET = 0x8;
		bufF1.bufferEnd = &bufF1.data[bufferSize-1];	
		bufF1.bufferBegin = &bufF1.data[0];
		bufF1.head = bufF1.bufferBegin;
		bufF1.tail = bufF1.bufferBegin;	
	}		
	
		uart->CTRLA |= USART_RXCINTLVL_MED_gc;
	switch(baud){
		case (1200):
			uart->CTRLB = USART_CTRLB_1200;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_1200;
			uart->BAUDCTRLB = USART_BAUDCTRLB_1200;
		break;
		case (4800):
			uart->CTRLB = USART_CTRLB_4800;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_4800;
			uart->BAUDCTRLB = USART_BAUDCTRLB_4800;
		break;
		case (9600):
			uart->CTRLB = USART_CTRLB_9600;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_9600;
			uart->BAUDCTRLB = USART_BAUDCTRLB_9600;
		break;
		case (14400):
			uart->CTRLB = USART_CTRLB_14400;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_14400;
			uart->BAUDCTRLB = USART_BAUDCTRLB_14400;
		break;
		case (19200):
			uart->CTRLB = USART_CTRLB_19200;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_19200;
			uart->BAUDCTRLB = USART_BAUDCTRLB_19200;
		break;
		case (28800):
			uart->CTRLB = USART_CTRLB_28800;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_28800;
			uart->BAUDCTRLB = USART_BAUDCTRLB_28800;
		break;
		case (38400):
			uart->CTRLB = USART_CTRLB_38400;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_38400;
			uart->BAUDCTRLB = USART_BAUDCTRLB_38400;
		break;
		case (56000):
			uart->CTRLB = USART_CTRLB_56000;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_56000;
			uart->BAUDCTRLB = USART_BAUDCTRLB_56000;
		break;
		case (57600):
			uart->CTRLB = USART_CTRLB_57600;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_57600;
			uart->BAUDCTRLB = USART_BAUDCTRLB_57600;
		break;
		case (115200):
			uart->CTRLB = USART_CTRLB_115200;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_115200;
			uart->BAUDCTRLB = USART_BAUDCTRLB_115200;
		break;
		case (230400):
			uart->CTRLB = USART_CTRLB_230400;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_230400;
			uart->BAUDCTRLB = USART_BAUDCTRLB_230400;
		break;
		default:
		
//			invalid baud rate defaulting to 9600		
		
			uart->CTRLB = USART_CTRLB_9600;
			uart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			uart->BAUDCTRLA = USART_BAUDCTRLA_9600;
			uart->BAUDCTRLB = USART_BAUDCTRLB_9600;
		break;
	}
	
	
	
}
