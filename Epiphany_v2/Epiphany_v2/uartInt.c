/*
 * uart.c
 *
 * Created: 7/7/2011 9:55:17 PM
 *  Author: Tim
 */ 
#include "uartInt.h"


bufTx_t	bufTxC0 = {&bufTxC0.data[0],&bufTxC0.data[bufferSizeTx-1],&bufTxC0.data[0],&bufTxC0.data[0],0},
		bufTxD0 = {&bufTxD0.data[0],&bufTxD0.data[bufferSizeTx-1],&bufTxD0.data[0],&bufTxD0.data[0],0},
		bufTxE0 = {&bufTxE0.data[0],&bufTxE0.data[bufferSizeTx-1],&bufTxE0.data[0],&bufTxE0.data[0],0};
			
bufRx_t	bufRxC0 = {&bufRxC0.data[0],&bufRxC0.data[bufferSizeRx-1],&bufRxC0.data[0],&bufRxC0.data[0],0},
		bufRxD0 = {&bufRxD0.data[0],&bufRxD0.data[bufferSizeRx-1],&bufRxD0.data[0],&bufRxD0.data[0],0},
		bufRxE0 = {&bufRxE0.data[0],&bufRxE0.data[bufferSizeRx-1],&bufRxE0.data[0],&bufRxE0.data[0],0};


#ifdef enableUartC0
FILE usartC0_str = FDEV_SETUP_STREAM(usartC0_putchar, uartC0_getchar, _FDEV_SETUP_RW);
#endif

#ifdef enableUartD0
FILE usartD0_str = FDEV_SETUP_STREAM(usartD0_putchar, uartD0_getchar, _FDEV_SETUP_RW);
#endif

#ifdef enableUartE0
FILE usartE0_str = FDEV_SETUP_STREAM(usartE0_putchar, uartE0_getchar, _FDEV_SETUP_RW);
#endif



//grabs byte from tx buffer
int usart_putchar(bufTx_t *buffer)
{
	if (buffer->tail == buffer->bufferEnd){
		uint8_t temp = *buffer->tail;
		buffer->tail = buffer->bufferBegin;
		return temp;
	}
	else return *buffer->tail++;	
}



int usart_getchar(bufRx_t *buffer){
	if (buffer->tail == buffer->bufferEnd){
		uint8_t temp = *buffer->tail;
		buffer->tail = buffer->bufferBegin;
		return temp;
	}
	else return *buffer->tail++;
}

//store Tx data in tx fifo
void usartStoreTx(USART_t *usart, bufTx_t *buffer, char c)
{
	if(buffer->head == buffer->bufferEnd){
		*buffer->head = c;
		buffer->head = buffer->bufferBegin;
	}
	else *buffer->head++ = c;
	if(usart->STATUS & USART_DREIF_bm) usart->DATA = usart_putchar(buffer); 
}

void usartStoreRx(bufRx_t *buffer, char c)
{
	if(buffer->head == buffer->bufferEnd){
		*buffer->head = c;
		buffer->head = buffer->bufferBegin;	
	}		
	else *buffer->head++ = c;
}

uint8_t usartDataInbufRx(bufRx_t *buffer){
	if(buffer->head == buffer->tail) return 0;	//no data to be read
	else return 1;	
}

uint8_t usartDataInbufTx(bufTx_t *buffer){
	if(buffer->head == buffer->tail)
		return 0;	//no data to be read
	else return 1;
}


ISR(USARTC0_RXC_vect){
	usartStoreRx(&bufRxC0,USARTC0.DATA);
}

ISR(USARTD0_RXC_vect){
	usartStoreRx(&bufRxD0,USARTD0.DATA);
}

ISR(USARTE0_RXC_vect){
	usartStoreRx(&bufRxE0,USARTE0.DATA);
}

ISR(USARTC0_TXC_vect){
	if(usartDataInbufTx(&bufTxC0)){ 
	while(!(USARTC0.STATUS & USART_DREIF_bm));
	USARTC0.DATA = usart_putchar(&bufTxC0); }
}

ISR(USARTD0_TXC_vect){
	if(usartDataInbufTx(&bufTxD0)) USARTD0.DATA = usart_putchar(&bufTxD0);
}

ISR(USARTE0_TXC_vect){
	if(usartDataInbufTx(&bufTxC0)) USARTE0.DATA = usart_putchar(&bufTxE0);
}



//initialization functions for the uarts
void uartInit(USART_t *usart, long baud)
{
	PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;					
	
		usart->CTRLA |= USART_RXCINTLVL_MED_gc | USART_TXCINTLVL_HI_gc;
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
