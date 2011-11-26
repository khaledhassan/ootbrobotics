/*
 * uart.c
 *
 * Created: 11/12/2011 12:18:09 AM
 *  Author: bfc
 */ 

#include "uart.h"

//FILE	uart_str = FDEV_SETUP_STREAM(uart_putchar,uart_getchar,_FDEV_SETUP_RW)


struct Buffer{
	const uint8_t *bufferBegin;
	const uint8_t *bufferEnd;
	uint8_t *head;
	uint8_t *tail;
	uint8_t data[bufferSize];
}buffer;

void uartInit(void){

UBRRH = 0;//set for baud of 230400... dang fast
UBRRL = 2;

UCSRB = _BV(RXCIE) | _BV(RXEN) ;//holding off on tx enable as of right now it may be better to simply receive data with the tx line as a sort of flow control 
}

void uart_putchar(char c,FILE *unused)
{
	while(!(UCSRA & UDRE));
	UDR = c;
}

int uart_getchar(FILE *stream){
	
	if (buffer.tail == buffer.bufferEnd){
		uint8_t temp = *buffer.tail;
		buffer.tail = buffer.bufferBegin;
		return temp;
	}
	else return *buffer.tail++;
}

void store(char c){
	if(buffer.head == buffer.bufferEnd){
		*buffer.head = c;
		buffer.head = buffer.bufferBegin;	
	}		
	else *buffer.head++ = c;
}

uint8_t dataInbuffer(void){
	if(buffer.head == buffer.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}
ISR(USART_RX_vect){
	store(UDR);
}

