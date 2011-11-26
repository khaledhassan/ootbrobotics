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

#define bufferSize	16

void uartInit(void);

FILE	uart_str;

#endif /* UART_H_ */