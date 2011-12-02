/*
 * uart.h
 *
 * Created: 11/12/2011 12:09:47 AM
 *  Author: bfc
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdio.h>

#define bufferSize	32

struct Buffer{
	uint8_t *head;
	uint8_t *tail;
	uint8_t data[bufferSize];
}buffer;


#define uartBufferBegin &buffer.data[0]
#define uartBufferEnd	&buffer.data[bufferSize-1]

void uartInit(void);

FILE	uart_str;

#endif /* UART_H_ */