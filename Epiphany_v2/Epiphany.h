/*
 * Epiphany.h
 *
 * Created: 8/29/2013 1:01:25 AM
 *  Author: Tim
 */ 


#ifndef EPIPHANY_H_
#define EPIPHANY_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "clock.h"
#include "utility.h"

#ifndef __AVR_ATxmega32A4U__

#include "adc.h"
#include "ATtinyServo.h"
#include "lcd.h"
#include "motor.h"
#include "RTC.h"
#include "uart.h"

#else

//#include "adc_a4.h"
//#include "uart_a4.h"

#endif

void setup();

void loop();




#endif /* EPIPHANY_H_ */