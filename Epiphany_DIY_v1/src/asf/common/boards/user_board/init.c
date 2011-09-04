/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	
	
	/*board specific port configs*/
	
	//set the direction on tx lines.  This may actually be unnecessary, but it doesn't hurt.
	
#if (motorCtrlMode == quadMode)	
	PORTF.DIRSET =	0x0F;			//Motor PWM lines
	PORTK.DIRSET =	0xFF;			//Motor direction lines
#elif (motorCtrlMode == dualModeDoubleChip)
	PORTF.DIRSET =	0x0A;			//Motor PWM lines
	PORTK.DIRSET =	0xCC;			//Motor direction lines
#elif (motorCtrlMode == dualModeSingleChip)
	PORTF.DIRSET =	0x0C;			//Motor PWM lines
	PORTK.DIRSET =	0x0C;			//Motor direction lines	
#else
	//do nothing motors are disconnected
#endif	

	PORTR.DIRSET =	0x02;			//Debug Led

/*This snippet of code is used to set the clock frequency of the MCU to 32MHz*/
	#ifdef F_CPU
		#if (F_CPU == 32000000)
		OSC.CTRL |= OSC_RC32MEN_bm;
		while(!(OSC.STATUS & OSC_RC32MRDY_bm));
		CCP = CCP_IOREG_gc;
		CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
		#else
		//do nothing 2000000Hz clock enabled by default
		#endif
	#endif	
	
	//if not disconnected motor drivers will be initialized
	motorInit();
	/*if motorInit does not compile this is due to the path ".." not being defined.
	fix this by using the file menu as follows Project/"Project Name" Properties/Toolchain/Directories/Include Paths
	simply add .. into the include paths which will cause the compiler to look into the main project directory
	in addition to the src folder.  By default the compiler does not do this, but oddly enough all new files
	are added directly to the main project folder.  Super intelligent I know*/	
}
