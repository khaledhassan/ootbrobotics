/*
 * uart.c
 *
 * Created: 7/7/2011 9:55:17 PM
 *  Author: Tim
 */ 
#include "uart.h"

//sets up all of the streams

FILE uartC0_str = FDEV_SETUP_STREAM(uartC0_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uartC1_str = FDEV_SETUP_STREAM(uartC1_putchar, NULL, _FDEV_SETUP_WRITE);

FILE uartD0_str = FDEV_SETUP_STREAM(uartD0_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uartD1_str = FDEV_SETUP_STREAM(uartD1_putchar, NULL, _FDEV_SETUP_WRITE);

FILE uartE0_str = FDEV_SETUP_STREAM(uartE0_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uartE1_str = FDEV_SETUP_STREAM(uartE1_putchar, NULL, _FDEV_SETUP_WRITE);

FILE uartF0_str = FDEV_SETUP_STREAM(uartF0_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uartF1_str = FDEV_SETUP_STREAM(uartF1_putchar, NULL, _FDEV_SETUP_WRITE);

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

//initialization functions for the uarts
void uartInit(USART_t *uart, long baud)
{
	if (uart == &USARTC0) PORTC.DIRSET = 0x8;	
	else if (uart == &USARTC1) PORTC.DIRSET = 0x80;	
	else if (uart == &USARTD0) PORTD.DIRSET = 0x8;	
	else if (uart == &USARTD1) PORTD.DIRSET = 0x80;	
	else if (uart == &USARTE0) PORTE.DIRSET = 0x8;	
	else if (uart == &USARTE1) PORTE.DIRSET = 0x80;	
	else if (uart == &USARTF0) PORTF.DIRSET = 0x8;	
	else if (uart == &USARTF1) PORTF.DIRSET = 0x80;	
	

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
