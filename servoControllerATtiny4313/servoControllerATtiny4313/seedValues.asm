/*
 * seedValues.asm
 *
 *  Created: 11/6/2011 11:56:57 PM
 *   Author: bfc
 */ 
 			LDI		r16,low(1*seedMultiplier)	
			STS		(timerval + 0),r16
			LDI		r16,high(1*seedMultiplier)	
			STS		(timerval+1),r16

			LDI		r16,low(2*seedMultiplier)	
			STS		(timerval + 2),r16
			LDI		r16,high(2*seedMultiplier)	
			STS		(timerval+3),r16

			LDI		r16,low(3*seedMultiplier)	
			STS		(timerval + 4),r16
			LDI		r16,high(3*seedMultiplier)	
			STS		(timerval+5),r16

			LDI		r16,low(4*seedMultiplier)	
			STS		(timerval + 6),r16
			LDI		r16,high(4*seedMultiplier)	
			STS		(timerval+7),r16

			LDI		r16,low(5*seedMultiplier)	
			STS		(timerval + 8),r16
			LDI		r16,high(5*seedMultiplier)	
			STS		(timerval+9),r16

			LDI		r16,low(6*seedMultiplier)	
			STS		(timerval + 10),r16
			LDI		r16,high(6*seedMultiplier)	
			STS		(timerval+11),r16

			LDI		r16,low(7*seedMultiplier)	
			STS		(timerval + 12),r16
			LDI		r16,high(7*seedMultiplier)	
			STS		(timerval+13),r16

			LDI		r16,low(8*seedMultiplier)	
			STS		(timerval + 14),r16
			LDI		r16,high(8*seedMultiplier)	
			STS		(timerval+15),r16

			LDI		r16,low(9*seedMultiplier)	
			STS		(timerval + 16),r16
			LDI		r16,high(9*seedMultiplier)	
			STS		(timerval+17),r16

			LDI		r16,low(10*seedMultiplier)	
			STS		(timerval + 18),r16
			LDI		r16,high(10*seedMultiplier)	
			STS		(timerval+19),r16

			LDI		r16,low(11*seedMultiplier)	
			STS		(timerval + 20),r16
			LDI		r16,high(11*seedMultiplier)	
			STS		(timerval+21),r16

			LDI		r16,low(12*seedMultiplier)	
			STS		(timerval + 22),r16
			LDI		r16,high(12*seedMultiplier)	
			STS		(timerval+23),r16

			LDI		r16,low(13*seedMultiplier)	
			STS		(timerval + 24),r16
			LDI		r16,high(13*seedMultiplier)	
			STS		(timerval+25),r16

			LDI		r16,low(14*seedMultiplier)	
			STS		(timerval + 26),r16
			LDI		r16,high(14*seedMultiplier)	
			STS		(timerval+27),r16

			LDI		r16,low(15*seedMultiplier)	
			STS		(timerval + 28),r16
			LDI		r16,high(15*seedMultiplier)	
			STS		(timerval+29),r16

			LDI		r16,low(16*seedMultiplier)	
			STS		(timerval + 30),r16
			LDI		r16,high(16*seedMultiplier)	
			STS		(timerval+31),r16

			LDI		r16,low(17*seedMultiplier)	
			STS		(timerval + 32),r16
			LDI		r16,high(17*seedMultiplier)	
			STS		(timerval+33),r16

			LDI		r16,low(18*seedMultiplier)	
			STS		(timerval + 34),r16
			LDI		r16,high(18*seedMultiplier)	
			STS		(timerval+35),r16

			LDI		r16,low(19*seedMultiplier)	
			STS		(timerval + 36),r16
			LDI		r16,high(19*seedMultiplier)	
			STS		(timerval+37),r16

			LDI		r16,low(20*seedMultiplier)	
			STS		(timerval + 38),r16
			LDI		r16,high(20*seedMultiplier)	
			STS		(timerval+39),r16

			LDI		r16,low(21*seedMultiplier)	
			STS		(timerval + 40),r16
			LDI		r16,high(21*seedMultiplier)	
			STS		(timerval+41),r16

			LDI		r16,low(22*seedMultiplier)	
			STS		(timerval + 42),r16
			LDI		r16,high(22*seedMultiplier)	
			STS		(timerval+43),r16

			LDI		r16,low(23*seedMultiplier)	
			STS		(timerval + 44),r16
			LDI		r16,high(23*seedMultiplier)	
			STS		(timerval+45),r16

			LDI		r16,low(24*seedMultiplier)	
			STS		(timerval + 46),r16
			LDI		r16,high(24*seedMultiplier)	
			STS		(timerval+47),r16

			RET
