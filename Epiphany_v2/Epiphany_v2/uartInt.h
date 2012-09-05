/*
 * uart.h
 *
 * Created: 7/7/2011 9:55:37 PM
 *  Author: Tim
 */ 

#ifndef UART_H_
#define UART_H_

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define bufferSizeRx	64
#define bufferSizeTx	64

#define enableUartC0	
#define enableUartD0
#define enableUartE0

//1200
#define BAUD1200	3331				
#define USART_BAUDCTRLA_1200	BAUD1200
#define USART_BAUDCTRLB_1200	0xC0 | (uint16_t)(0x0FFF & BAUD1200>>8)
#define USART_CTRLB_1200		USART_RXEN_bm | USART_TXEN_bm

//2400
#define BAUD2400	3329			
#define USART_BAUDCTRLA_2400	BAUD2400
#define USART_BAUDCTRLB_2400	0xE0 | (uint16_t)(0x0FFF & BAUD2400>>8)
#define USART_CTRLB_2400		USART_RXEN_bm | USART_TXEN_bm

//4800
#define BAUD4800	3325			
#define USART_BAUDCTRLA_4800	BAUD4800
#define USART_BAUDCTRLB_4800	0xD0 | (uint16_t)(0x0FFF & BAUD4800>>8)
#define USART_CTRLB_4800		USART_RXEN_bm | USART_TXEN_bm

//9600
#define BAUD9600	3317			
#define USART_BAUDCTRLA_9600	BAUD9600
#define USART_BAUDCTRLB_9600	0xC0 | (uint16_t)(0x0FFF & BAUD9600>>8)
#define USART_CTRLB_9600		USART_RXEN_bm | USART_TXEN_bm

//14400
#define BAUD14400	2206			
#define USART_BAUDCTRLA_14400	BAUD14400
#define USART_BAUDCTRLB_14400	0xC0 | (uint16_t)(0x0FFF & BAUD14400>>8)
#define USART_CTRLB_14400		USART_RXEN_bm | USART_TXEN_bm

//19200
#define BAUD19200	3317			
#define USART_BAUDCTRLA_19200	BAUD19200
#define USART_BAUDCTRLB_19200	0xC0 | (uint16_t)(0x0FFF & BAUD19200>>8)
#define USART_CTRLB_19200		USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm

//28800
#define BAUD28800	2206			
#define USART_BAUDCTRLA_28800	BAUD28800
#define USART_BAUDCTRLB_28800	0xC0 | (uint16_t)(0x0FFF & BAUD28800>>8)
#define USART_CTRLB_28800		USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm

//38400
#define BAUD38400	3301			
#define USART_BAUDCTRLA_38400	BAUD38400
#define USART_BAUDCTRLB_38400	0xB0 | (uint16_t)(0x0FFF & BAUD38400>>8)
#define USART_CTRLB_38400		USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm

//56000
#define BAUD56000	2254			
#define USART_BAUDCTRLA_56000	BAUD56000
#define USART_BAUDCTRLB_56000	0xB0 | (uint16_t)(0x0FFF & BAUD56000>>8)
#define USART_CTRLB_56000		USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm

//57600
#define BAUD57600	2190			
#define USART_BAUDCTRLA_57600	BAUD57600
#define USART_BAUDCTRLB_57600	0xB0 | (uint16_t)(0x0FFF & BAUD57600>>8)
#define USART_CTRLB_57600		USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm

//115200
#define BAUD115200	2158			
#define USART_BAUDCTRLA_115200	BAUD115200
#define USART_BAUDCTRLB_115200	0xA0 | (uint16_t)(0x0FFF & BAUD115200>>8)
#define USART_CTRLB_115200		USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm

//125000
#define BAUD125000	1984		
#define USART_BAUDCTRLA_125000	BAUD125000
#define USART_BAUDCTRLB_125000	0xA0 | (uint16_t)(0x0FFF & BAUD125000>>8)
#define USART_CTRLB_125000		USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm

//230400
#define BAUD230400	2094			
#define USART_BAUDCTRLA_230400	BAUD230400
#define USART_BAUDCTRLB_230400	0x90 | (uint16_t)(0x0FFF & BAUD230400>>8)
#define USART_CTRLB_230400		USART_RXEN_bm | USART_TXEN_bm | USART_CLK2X_bm

//FIFOS

typedef struct{
	uint8_t *bufferBegin;
	uint8_t *bufferEnd;
	uint8_t *head;
	uint8_t *tail;
	uint8_t data[bufferSizeRx];
}bufRx_t;


typedef struct{
	uint8_t *bufferBegin;
	uint8_t *bufferEnd;
	uint8_t *head;
	uint8_t *tail;
	uint8_t data[bufferSizeTx];
}bufTx_t;

extern bufTx_t bufTxC0, bufTxD0, bufTxE0;
extern bufRx_t bufRxC0, bufRxD0, bufRxE0;


void uartInit(USART_t *usart, long baud);//inilization routine for uart modules.  uart = &USARTxn where x is C-F n is 0-1
int usart_putchar(bufTx_t *buffer);

int usart_getchar(bufRx_t *buffer);

void usartStoreTx(USART_t *usart, bufTx_t *buffer, char c);
void usartStoreRx(bufRx_t *buffer, char c);



static inline void usartC0_putchar(char c){
	usartStoreTx(&USARTC0,&bufTxC0, c);
}

static inline void usartD0_putchar(char c){
	usartStoreTx(&USARTD0,&bufTxD0, c);
}

static inline void usartE0_putchar(char c){
	usartStoreTx(&USARTE0,&bufTxE0, c);
}

static inline int uartC0_getchar(char c){
	return usart_getchar(&bufRxC0);
}

static inline int uartD0_getchar(char c){
	return usart_getchar(&bufRxD0);
}

static inline int uartE0_getchar(char c){
	return usart_getchar(&bufRxE0);
}


FILE usartC0_str;

FILE usartD0_str;

FILE usartE0_str;

#endif /* UART_H_ */