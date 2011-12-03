#include <htc.h>

/*
 * initialization routine of the 16-bit timer module (timer1)
 */
void timerInit(){
    //timer1 config for servo timing
    T1CON = 0x21; //timer1 enabled clocked at 2MHz
    T1GCON &= ~0x80; //timer1 clocks intepedently from gate
//	T2CON = 0x5;
    PIE1 |= 0x01; //enables timer1 ovf interrupt

    /*
     * timer will not overflow at the correct time initialy.  However
     * this will not matter since nothing happens the first cycle.  The timer
     * will be initialized completely after the first overflow and every one
     * thereafter.
    */
}