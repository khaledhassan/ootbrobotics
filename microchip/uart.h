#ifndef UART_H_
#define UART_H_


#define uartRxIntEnable()	(PIE1 |= 0x20)
#define uartRxIntDisable()	(PIE1 &= ~0x20)

#define baud    57600

#if(baud == 9600)


#define sprgh_enum  416

#define BAUDCON_msk 0x08
#define SPBRGH_msk   (sprgh_enum >> 8)
#define SPBRGL_msk   (sprgh_enum & 0x00FF)
#define TXSTA_msk   0x24
#define RCSTA_msk   0x90


#elif (baud == 57600)


#define sprgh_enum  138


#define BAUDCON_msk 0x08
#define SPBRGH_msk   (sprgh_enum >> 8)
#define SPBRGL_msk   (sprgh_enum & 0x00FF)
#define TXSTA_msk   0x24
#define RCSTA_msk   0x90

#elif (baud == 115200)
//sync = 1
//brg16 = 1

#define sprgh_enum  68


#define BAUDCON_msk 0x08
#define SPBRGH_msk   (sprgh_enum >> 8)
#define SPBRGL_msk   (sprgh_enum & 0x00FF)
#define TXSTA_msk   0x24
#define RXSTA_msk   0x90
#endif

//bitmasks for uart configurations




/*
 Uart initialization routine
 */
void uartInit();
/*
 function is used to send a charater through the Uart module
 */
void uart_putC(char c);



#endif