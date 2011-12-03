#include <htc.h>
#include "uart.h"

void uartInit(){
    //uart config
    BAUDCON |= BAUDCON_msk;
    SPBRGH = SPBRGH_msk;
    SPBRGL = SPBRGL_msk;
    RCSTA |= RCSTA_msk; //config rx
    TXSTA |= TXSTA_msk; //comfig tx
	PIE1 |= 0x20;
	ANSELA &= 0x20;	//Microchip you and I are gonna fight....For Realz this took me way to long to find
}

void uart_putC(char c) {
    while (!(TXSTA & 0x02)){} //wait until transmitter is ready to send
    TXREG = c;
}
