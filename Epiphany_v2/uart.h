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


#define bufferSize	64

#define PORT_USARTTX0_msk	0x08
#define PORT_USARTTX1_msk	0x80


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

typedef struct{
	uint8_t *bufferBegin;
	uint8_t *bufferEnd;
	uint8_t *head;
	uint8_t *tail;
	uint8_t data[bufferSize];
}buf_t;

buf_t	bufRxC0,bufTxC0,
		bufRxC1,bufTxC1,
		bufRxD0,bufTxD0,
		bufRxD1,bufTxD1,
		bufRxE1,bufTxE1,
		bufRxF0,bufTxF0,
		bufRxF1,bufTxF1;
		

void usartInit(USART_t *uart, long baud);//inilization routine for uart modules.  uart = &USARTxn where x is C-F n is 0-1

static inline void usbInit(long baud){ usartInit(&USARTC0,baud);}
static inline void xbeeInit(long baud){ usartInit(&USARTE1,baud);}
	

void usart_putc(USART_t *usart, buf_t *buffer, char c);
uint8_t usart_getc(buf_t *buffer);
void usart_Put(USART_t *usart, buf_t *buffer, uint8_t *packet,uint16_t packetLength);
uint8_t bufferRead(buf_t *buffer);
void bufferWrite(buf_t *buffer, char c);
uint8_t dataInBuf(buf_t *buffer);

static inline uint8_t dataInBufC0(){ return	dataInBuf(&bufRxC0);}
static inline uint8_t dataInBufC1(){ return	dataInBuf(&bufRxC1);}
static inline uint8_t dataInBufD0(){ return	dataInBuf(&bufRxD0);}
static inline uint8_t dataInBufD1(){ return	dataInBuf(&bufRxD1);}
static inline uint8_t dataInBufE1(){ return	dataInBuf(&bufRxE1);}
static inline uint8_t dataInBufF0(){ return	dataInBuf(&bufRxF0);}
static inline uint8_t dataInBufF1(){ return	dataInBuf(&bufRxF1);}

static inline void usartC0_putc(char c){usart_putc(&USARTC0,&bufTxC0,c);}
static inline void usartC1_putc(char c){usart_putc(&USARTC1,&bufTxC1,c);}
static inline void usartD0_putc(char c){usart_putc(&USARTD0,&bufTxD0,c);}
static inline void usartD1_putc(char c){usart_putc(&USARTD1,&bufTxD1,c);}
static inline void usartE1_putc(char c){usart_putc(&USARTE1,&bufTxE1,c);}
static inline void usartF0_putc(char c){usart_putc(&USARTF0,&bufTxF0,c);}
static inline void usartF1_putc(char c){usart_putc(&USARTF1,&bufTxF1,c);}

static inline uint8_t usartC0_getc(){ return usart_getc(&bufRxC0);}
static inline uint8_t usartC1_getc(){ return usart_getc(&bufRxC1);}
static inline uint8_t usartD0_getc(){ return usart_getc(&bufRxD0);}
static inline uint8_t usartD1_getc(){ return usart_getc(&bufRxD1);}
static inline uint8_t usartE1_getc(){ return usart_getc(&bufRxE1);}
static inline uint8_t usartF0_getc(){ return usart_getc(&bufRxF0);}
static inline uint8_t usartF1_getc(){ return usart_getc(&bufRxF1);}

FILE usartC0_str;
FILE usartC1_str;

FILE usartD0_str;
FILE usartD1_str;

FILE usartE1_str;

FILE usartF0_str;
FILE usartF1_str;

#define USB_str		usartC0_str
#define Xbee_str	usartE1_str

#define dataInBufUSB()	dataInBufC0()
#define dataInBufXbee()	dataInBufE1()


#endif /* UART_H_ */