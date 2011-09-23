/**
 * \file
 *
 * \brief User board definition template
 *
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

/* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
#include "motor.h"
#include "lcd.h"


#ifndef F_CPU
#define F_CPU 2000000
#endif


#define disconnected			0
#define dualModeDoubleChip		1
#define quadMode				2
#define dualModeSingleChip		3				


/*define the mode of motor control here. simply uncomment the mode you wish to use and comment all you do not want to use the module*/

//#define motorCtrlMode	dualModeDoubleChip
#define motorCtrlMode	quadMode
//#define motorCtrlMode	dualModeSingleChip

#ifndef motorCtrlMode
#define motorCtrlMode	disconnected
#warning "motors will remain disconnected until the motor control mode is selected in <asf/common/boards/user_board/user_board.h>"
#endif

#endif // USER_BOARD_H