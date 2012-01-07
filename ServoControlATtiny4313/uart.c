/*
 * uart.c
 *
 * Created: 11/12/2011 12:18:09 AM
 *  Author: bfc
 */ 

#include "uart.h"

void uartInit(void){

UBRRH = 0;//set for baud of 125000... dang fast
UBRRL = 5;

UCSRB	|= _BV(RXEN) ;//holding off on tx enable as of right now it may be better to simply receive data with the tx line as a sort of flow control 

buffer.head = uartBufferBegin;
buffer.tail = uartBufferBegin;

}


int uart_getchar(FILE *stream){
	bytesInBuffer--;
	if (buffer.tail == uartBufferEnd){
		uint8_t temp = *buffer.tail;
		buffer.tail = uartBufferBegin;
		return temp;
	}
	else return *buffer.tail++;
}

void uart_store(unsigned char c){
	bytesInBuffer++;
	if(buffer.head == uartBufferEnd){
		*buffer.head = c;
		buffer.head = uartBufferBegin;	
	}		
	else *buffer.head++ = c;
	servoDataIRQ();
}

uint8_t dataInbuffer(void){
	if(buffer.head == buffer.tail) return 0;	//no data to be read
	else return 1;							//data to be read
}

uint8_t getNumBytesInBuffer(void){
return bytesInBuffer;
}

void flush(void){
	buffer.head = buffer.tail;
	bytesInBuffer = 0;
}

ISR(USART_RX_vect){
	uart_store(UDR);	
}

