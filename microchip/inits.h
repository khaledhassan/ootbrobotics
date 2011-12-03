#ifndef INITS_H
#define INITS_H

#include <htc.h>
#include <pic.h>
#include <time.h>
#include "intdefs.h"
#include "uart.h"
#include "spi.h"
#include "timer.h"

void initializations(void);
#define sei()	(INTCON |= 0x80)		//global interrupt enable
#define cli()	(INTCON &= ~0x80)	//global interrupt disable
#define perIntEnable()	(INTCON |= 0x40)	//peripheral interrupt enable
#define perIntDisable()	(INTCON &= ~0x40)	//peripheral interrupt disable

#endif