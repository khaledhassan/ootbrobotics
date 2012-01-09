/*
 * uart.h
 *
 * Created: 11/12/2011 12:09:47 AM
 *  Author: bfc
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


uint8_t bytesInBuffer;

struct Buffer{
	uint8_t *head;
	uint8_t *tail;
	uint8_t data[bufferSize];
}buffer;

#define uartBufferBegin &buffer.data[0]
#define uartBufferEnd	&buffer.data[bufferSize-1]


void uartInit(void);
int uart_getchar(FILE *stream);
void uart_store(unsigned char c);
uint8_t dataInbuffer(void);
uint8_t getNumBytesInBuffer(void);
void flush(void);

#endif /* UART_H_ */