/*
 * uart.c
 *
 * Created: 7/7/2011 9:55:17 PM
 *  Author: Tim
 */ 
#include "uart.h"

buf_t	bufRxC0 = {&bufRxC0.data[0],&bufRxC0.data[bufferSize-1],&bufRxC0.data[0],&bufRxC0.data[0],0},
		bufTxC0 = {&bufTxC0.data[0],&bufTxC0.data[bufferSize-1],&bufTxC0.data[0],&bufTxC0.data[0],0},
				
		bufRxC1 = {&bufRxC1.data[0],&bufRxC1.data[bufferSize-1],&bufRxC1.data[0],&bufRxC1.data[0],0},
		bufTxC1 = {&bufTxC1.data[0],&bufTxC1.data[bufferSize-1],&bufTxC1.data[0],&bufTxC1.data[0],0},
				
		bufRxD0 = {&bufRxD0.data[0],&bufRxD0.data[bufferSize-1],&bufRxD0.data[0],&bufRxD0.data[0],0},
		bufTxD0 = {&bufTxD0.data[0],&bufTxD0.data[bufferSize-1],&bufTxD0.data[0],&bufTxD0.data[0],0},
				
		bufRxD1 = {&bufRxD1.data[0],&bufRxD1.data[bufferSize-1],&bufRxD1.data[0],&bufRxD1.data[0],0},
		bufTxD1 = {&bufTxD1.data[0],&bufTxD1.data[bufferSize-1],&bufTxD1.data[0],&bufTxD1.data[0],0},
				
		bufRxE1 = {&bufRxE1.data[0],&bufRxE1.data[bufferSize-1],&bufRxE1.data[0],&bufRxE1.data[0],0},
		bufTxE1 = {&bufTxE1.data[0],&bufTxE1.data[bufferSize-1],&bufTxE1.data[0],&bufTxE1.data[0],0},
				
		bufRxF0 = {&bufRxF0.data[0],&bufRxF0.data[bufferSize-1],&bufRxF0.data[0],&bufRxF0.data[0],0},				
		bufTxF0 = {&bufTxF0.data[0],&bufTxF0.data[bufferSize-1],&bufTxF0.data[0],&bufTxF0.data[0],0},
				
		bufRxF1 = {&bufRxF1.data[0],&bufRxF1.data[bufferSize-1],&bufRxF1.data[0],&bufRxF1.data[0],0},
		bufTxF1 = {&bufTxF1.data[0],&bufTxF1.data[bufferSize-1],&bufTxF1.data[0],&bufTxF1.data[0],0};

//sets up all of the streams
FILE usartC0_str = FDEV_SETUP_STREAM(usartC0_putc, usartC0_getc, _FDEV_SETUP_RW);

FILE usartC1_str = FDEV_SETUP_STREAM(usartC1_putc, usartC1_getc, _FDEV_SETUP_RW);

FILE usartD0_str = FDEV_SETUP_STREAM(usartD0_putc, usartD0_getc, _FDEV_SETUP_RW);

FILE usartD1_str = FDEV_SETUP_STREAM(usartD1_putc, usartD1_getc, _FDEV_SETUP_RW);

FILE usartE1_str = FDEV_SETUP_STREAM(usartE1_putc, usartE1_getc, _FDEV_SETUP_RW);

FILE usartF0_str = FDEV_SETUP_STREAM(usartF0_putc, usartF0_getc, _FDEV_SETUP_RW);

FILE usartF1_str = FDEV_SETUP_STREAM(usartF1_putc, usartF1_getc, _FDEV_SETUP_RW);

//these functions are used for outputing data from the uarts

void usart_putc(USART_t *usart, buf_t *buffer, char c)
{
	cli();
	bufferWrite((buf_t *)buffer,c);
	usart->CTRLA &= ~USART_DREINTLVL_gm;
	usart->CTRLA |= USART_DREINTLVL_LO_gc;	//setting this bit should cause the DRE interrupt to be triggered
	sei();
}

uint8_t usart_getc(buf_t *buffer)
{
	uint8_t temp;
	cli();
	temp = bufferRead((buf_t *) buffer);
	sei();
	return temp;
}

void usart_Put(USART_t *usart, buf_t *buffer, uint8_t *packet,uint16_t packetLength)
{
	cli();
	uint16_t i;
	for(i=0;i<packetLength;i++)
	{
		bufferWrite((buf_t *)buffer,packet[i]);
	}
	usart->CTRLA &= ~USART_DREINTLVL_gm;
	usart->CTRLA |= USART_DREINTLVL_LO_gc;	//setting this bit should cause the DRE interrupt to be triggered
	sei();
}

uint8_t bufferRead(buf_t *buffer){
	if (buffer->tail == buffer->bufferEnd){
		uint8_t temp = *buffer->tail;
		buffer->tail = buffer->bufferBegin;
		return temp;
	}
	else
	{
		return *buffer->tail++;
	}
}

void bufferWrite(buf_t *buffer, char c){
	if(buffer->head == buffer->bufferEnd){
		*buffer->head = c;
		buffer->head = buffer->bufferBegin;
	}
	else *buffer->head++ = c;
}

uint8_t dataInBuf(buf_t *buffer){
	if(buffer->head == buffer->tail) return 0;	//no data to be read
	else return 1;	
}

ISR(USARTC0_RXC_vect){
	bufferWrite(&bufRxC0,USARTC0.DATA);
}
ISR(USARTC1_RXC_vect){
	bufferWrite(&bufRxC1,USARTC1.DATA);
}
ISR(USARTD0_RXC_vect){
	bufferWrite(&bufRxD0,USARTD0.DATA);
}
ISR(USARTD1_RXC_vect){
	bufferWrite(&bufRxD1,USARTD1.DATA);
}
ISR(USARTE1_RXC_vect){
	bufferWrite(&bufRxE1,USARTE1.DATA);
}
ISR(USARTF0_RXC_vect){
	bufferWrite(&bufRxF0,USARTF0.DATA);
}
ISR(USARTF1_RXC_vect){
	bufferWrite(&bufRxF1,USARTF1.DATA);
}

ISR(USARTC0_DRE_vect)
{
	cli();
	if(dataInBuf(&bufTxC0))
	{
		USARTC0.DATA = bufferRead(&bufTxC0);		//this is used to send packets of data in quick bursts
	}
	else USARTC0.CTRLA &= ~USART_DREINTLVL_gm;
	sei();
}

ISR(USARTC1_DRE_vect)
{
	cli();
	if(dataInBuf(&bufTxC1))
	{
		USARTC1.DATA = bufferRead(&bufTxC1);		//this is used to send packets of data in quick bursts
	}
	else USARTC1.CTRLA &= ~USART_DREINTLVL_gm;
	sei();
}

ISR(USARTD0_DRE_vect)
{
	cli();
	if(dataInBuf(&bufTxD0))
	{
		USARTD0.DATA = bufferRead(&bufTxD0);		//this is used to send packets of data in quick bursts
	}
	else USARTD0.CTRLA &= ~USART_DREINTLVL_gm;
	sei();
}

ISR(USARTD1_DRE_vect)
{
	cli();
	if(dataInBuf(&bufTxD1))
	{
		USARTD1.DATA = bufferRead(&bufTxD1);		//this is used to send packets of data in quick bursts
	}
	else USARTD1.CTRLA &= ~USART_DREINTLVL_gm;
	sei();
}

ISR(USARTE1_DRE_vect)
{
	cli();
	if(dataInBuf(&bufTxE1))
	{
		USARTE1.DATA = bufferRead(&bufTxE1);		//this is used to send packets of data in quick bursts
	}
	else USARTE1.CTRLA &= ~USART_DREINTLVL_gm;
	sei();
}

ISR(USARTF0_DRE_vect)
{
	cli();
	if(dataInBuf(&bufTxF0))
	{
		USARTF0.DATA = bufferRead(&bufTxF0);		//this is used to send packets of data in quick bursts
	}
	else USARTF0.CTRLA &= ~USART_DREINTLVL_gm;
	sei();
}

ISR(USARTF1_DRE_vect)
{
	cli();
	if(dataInBuf(&bufTxF1))
	{
		USARTF1.DATA = bufferRead(&bufTxF1);		//this is used to send packets of data in quick bursts
	}
	else USARTF1.CTRLA &= ~USART_DREINTLVL_gm;
	sei();
}


//initialization functions for the uarts
void usartInit(USART_t *usart, long baud)
{
	switch((uint16_t)usart)
	{
		case ((uint16_t)&USARTC0):
			PORTC.DIRSET = PORT_USARTTX0_msk;
		break;
		case ((uint16_t)&USARTC1):
			PORTC.DIRSET = PORT_USARTTX1_msk;
		break;
		case ((uint16_t)&USARTD0):
			PORTD.DIRSET = PORT_USARTTX0_msk;
		break;
		case ((uint16_t)&USARTD1):
			PORTD.DIRSET = PORT_USARTTX1_msk;
		break;
		case ((uint16_t)&USARTE1):
			PORTE.DIRSET = PORT_USARTTX1_msk;
		break;
		case ((uint16_t)&USARTF0):
			PORTF.DIRSET = PORT_USARTTX0_msk;
		break;
		case ((uint16_t)&USARTF1):
			PORTF.DIRSET = PORT_USARTTX1_msk;
		break;
		
	}
	
	PMIC.CTRL |= PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;	
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
