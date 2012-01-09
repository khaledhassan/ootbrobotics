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
#include <asf.h>

#define	enableUartC0	
//#define enableUartC1
//#define enableUartD0
//#define enableUartD1
//#define enableUartE0
#define enableUartE1
//#define enableUartF0
//#define enableUartF1

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

void uartInit(USART_t *uart, long baud);//inilization routine for uart modules.  uart = &USARTxn where x is C-F n is 0-1
void uartF0_putchar(char c,FILE *unused);//uart output function
void uartF1_putchar(char c,FILE *unused);//uart output function
void uartE0_putchar(char c,FILE *unused);//uart output function
void uartE1_putchar(char c,FILE *unused);//uart output function
void uartD0_putchar(char c,FILE *unused);//uart output function
void uartD1_putchar(char c,FILE *unused);//uart output function
void uartC0_putchar(char c,FILE *unused);//uart output function
void uartC1_putchar(char c,FILE *unused);//uart output function


int uartC0_getchar(FILE *stream);
uint8_t dataInBufC0(void);
void storeC0(char c);

int uartC1_getchar(FILE *stream);
uint8_t dataInBufC1(void);
void storeC1(char c);

int uartD0_getchar(FILE *stream);
uint8_t dataInBufD0(void);
void storeD0(char c);

int uartD1_getchar(FILE *stream);
uint8_t dataInBufD1(void);
void storeD1(char c);


int uartE0_getchar(FILE *stream);
uint8_t dataInBufE0(void);
void storeE0(char c);

int uartE1_getchar(FILE *stream);
uint8_t dataInBufE1(void);
void storeE1(char c);

int uartF0_getchar(FILE *stream);
uint8_t dataInBufF0(void);
void storeF0(char c);

int uartF1_getchar(FILE *stream);
uint8_t dataInBufF1(void);
void storeF1(char c);

FILE uartC0_str;
FILE uartC1_str;

FILE uartD0_str;
FILE uartD1_str;

FILE uartE0_str;
FILE uartE1_str;

FILE uartF0_str;
FILE uartF1_str;

#define USB_str		uartC0_str
#define Xbee_str	uartE1_str
#define Servo_str	uartE0_str

#endif /* UART_H_ */