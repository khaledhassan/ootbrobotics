/*
 * uart.c
 *
 * Created: 7/7/2011 9:55:17 PM
 *  Author: Tim
 */ 
#include "uart.h"


bufRx_t			bufRxC0 = {&bufRxC0.data[0],&bufRxC0.data[bufferSizeRx-1],&bufRxC0.data[0],&bufRxC0.data[0],0},
				bufRxC1 = {&bufRxC1.data[0],&bufRxC1.data[bufferSizeRx-1],&bufRxC1.data[0],&bufRxC1.data[0],0},
				bufRxD0 = {&bufRxD0.data[0],&bufRxD0.data[bufferSizeRx-1],&bufRxD0.data[0],&bufRxD0.data[0],0},
				bufRxD1 = {&bufRxD1.data[0],&bufRxD1.data[bufferSizeRx-1],&bufRxD1.data[0],&bufRxD1.data[0],0},
				bufRxE1 = {&bufRxE1.data[0],&bufRxE1.data[bufferSizeRx-1],&bufRxE1.data[0],&bufRxE1.data[0],0},
				bufRxF0 = {&bufRxF0.data[0],&bufRxF0.data[bufferSizeRx-1],&bufRxF0.data[0],&bufRxF0.data[0],0},				
				bufRxF1 = {&bufRxF1.data[0],&bufRxF1.data[bufferSizeRx-1],&bufRxF1.data[0],&bufRxF1.data[0],0};

//sets up all of the streams
FILE usartC0_str = FDEV_SETUP_STREAM(usartC0_putchar, usartC0_getchar, _FDEV_SETUP_RW);

FILE usartC1_str = FDEV_SETUP_STREAM(usartC1_putchar, usartC1_getchar, _FDEV_SETUP_RW);

FILE usartD0_str = FDEV_SETUP_STREAM(usartD0_putchar, usartD0_getchar, _FDEV_SETUP_RW);

FILE usartD1_str = FDEV_SETUP_STREAM(usartD1_putchar, usartD1_getchar, _FDEV_SETUP_RW);

FILE usartE1_str = FDEV_SETUP_STREAM(usartE1_putchar, usartE1_getchar, _FDEV_SETUP_RW);

FILE usartF0_str = FDEV_SETUP_STREAM(usartF0_putchar, usartF0_getchar, _FDEV_SETUP_RW);

FILE usartF1_str = FDEV_SETUP_STREAM(usartF1_putchar, usartF1_getchar, _FDEV_SETUP_RW);


//these functions are used for outputing data from the uarts

void usart_putchar(USART_t *usart, char c)
{
	while(!(usart->STATUS & USART_DREIF_bm));
	usart->DATA = c;
}

uint8_t usart_getchar(bufRx_t *buffer){	
	if (buffer->tail == buffer->bufferEnd){
		uint8_t temp = *buffer->tail;
		buffer->tail = buffer->bufferBegin;
		return temp;
	}
	else return *buffer->tail++;
}

void usartStore(bufRx_t *buffer, char c){
	if(buffer->head == buffer->bufferEnd){
		*buffer->head = c;
		buffer->head = buffer->bufferBegin;	
	}		
	else *buffer->head++ = c;
}

uint8_t dataInBuf(bufRx_t *buffer){
	if(buffer->head == buffer->tail) return 0;	//no data to be read
	else return 1;	
}

ISR(USARTC0_RXC_vect){
	usartStore(&bufRxC0,USARTC0.DATA);
}
ISR(USARTC1_RXC_vect){
	usartStore(&bufRxC1,USARTC1.DATA);
}
ISR(USARTD0_RXC_vect){
	usartStore(&bufRxD0,USARTD0.DATA);
}
ISR(USARTD1_RXC_vect){
	usartStore(&bufRxD1,USARTD1.DATA);
}
ISR(USARTE1_RXC_vect){
	usartStore(&bufRxE1,USARTE1.DATA);
}
ISR(USARTF0_RXC_vect){
	usartStore(&bufRxF0,USARTF0.DATA);
}
ISR(USARTF1_RXC_vect){
	usartStore(&bufRxF1,USARTF1.DATA);
}


//initialization functions for the uarts
void usartInit(USART_t *usart, long baud)
{
	PMIC.CTRL |= PMIC_MEDLVLEX_bm;	
		usart->CTRLA |= USART_RXCINTLVL_MED_gc;
	switch(baud){
		case (1200):
			usart->CTRLB = USART_CTRLB_1200;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_1200;
			usart->BAUDCTRLB = USART_BAUDCTRLB_1200;
		break;
		case (4800):
			usart->CTRLB = USART_CTRLB_4800;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_4800;
			usart->BAUDCTRLB = USART_BAUDCTRLB_4800;
		break;
		case (9600):
			usart->CTRLB = USART_CTRLB_9600;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_9600;
			usart->BAUDCTRLB = USART_BAUDCTRLB_9600;
		break;
		case (14400):
			usart->CTRLB = USART_CTRLB_14400;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_14400;
			usart->BAUDCTRLB = USART_BAUDCTRLB_14400;
		break;
		case (19200):
			usart->CTRLB = USART_CTRLB_19200;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_19200;
			usart->BAUDCTRLB = USART_BAUDCTRLB_19200;
		break;
		case (28800):
			usart->CTRLB = USART_CTRLB_28800;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_28800;
			usart->BAUDCTRLB = USART_BAUDCTRLB_28800;
		break;
		case (38400):
			usart->CTRLB = USART_CTRLB_38400;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_38400;
			usart->BAUDCTRLB = USART_BAUDCTRLB_38400;
		break;
		case (56000):
			usart->CTRLB = USART_CTRLB_56000;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_56000;
			usart->BAUDCTRLB = USART_BAUDCTRLB_56000;
		break;
		case (57600):
			usart->CTRLB = USART_CTRLB_57600;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_57600;
			usart->BAUDCTRLB = USART_BAUDCTRLB_57600;
		break;
		case (115200):
			usart->CTRLB = USART_CTRLB_115200;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_115200;
			usart->BAUDCTRLB = USART_BAUDCTRLB_115200;
		break;
		case (125000):
			usart->CTRLB = USART_CTRLB_125000;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_125000;
			usart->BAUDCTRLB = USART_BAUDCTRLB_125000;
		break;
		case (230400):
			usart->CTRLB = USART_CTRLB_230400;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_230400;
			usart->BAUDCTRLB = USART_BAUDCTRLB_230400;
		break;
		default:
		
		//invalid baud rate defaulting to 9600		
		
			usart->CTRLB = USART_CTRLB_9600;
			usart->CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc;
			usart->BAUDCTRLA = USART_BAUDCTRLA_9600;
			usart->BAUDCTRLB = USART_BAUDCTRLB_9600;
		break;
	}
}
