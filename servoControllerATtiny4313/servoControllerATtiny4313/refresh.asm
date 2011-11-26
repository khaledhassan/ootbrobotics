/*
 * refresh.asm
 *
 *  Created: 11/6/2011 10:41:37 PM
 *   Author: bfc
 */ 

 refresh:
		LDS		r16,(servoBufferRegs + 0)
		STS		(timerval + 0),r16

		LDS		r16,(servoBufferRegs + 1)
		STS		(timerval + 1),r16

		LDS		r16,(servoBufferRegs + 2)
		STS		(timerval + 2),r16

		LDS		r16,(servoBufferRegs + 3)
		STS		(timerval + 3),r16

		LDS		r16,(servoBufferRegs + 4)
		STS		(timerval + 4),r16

		LDS		r16,(servoBufferRegs + 5)
		STS		(timerval + 5),r16

		LDS		r16,(servoBufferRegs + 6)
		STS		(timerval + 6),r16

		LDS		r16,(servoBufferRegs + 7)
		STS		(timerval + 7),r16

		LDS		r16,(servoBufferRegs + 8)
		STS		(timerval + 8),r16

		LDS		r16,(servoBufferRegs + 9)
		STS		(timerval + 9),r16

		LDS		r16,(servoBufferRegs + 10)
		STS		(timerval + 10),r16

		LDS		r16,(servoBufferRegs + 11)
		STS		(timerval + 11),r16

		LDS		r16,(servoBufferRegs + 12)
		STS		(timerval + 12),r16

		LDS		r16,(servoBufferRegs + 13)
		STS		(timerval + 13),r16

		LDS		r16,(servoBufferRegs + 14)
		STS		(timerval + 14),r16

		LDS		r16,(servoBufferRegs + 15)
		STS		(timerval + 15),r16

		LDS		r16,(servoBufferRegs + 16)
		STS		(timerval + 16),r16

		LDS		r16,(servoBufferRegs + 17)
		STS		(timerval + 17),r16

		LDS		r16,(servoBufferRegs + 18)
		STS		(timerval + 18),r16

		LDS		r16,(servoBufferRegs + 19)
		STS		(timerval + 19),r16

		LDS		r16,(servoBufferRegs + 20)
		STS		(timerval + 20),r16

		LDS		r16,(servoBufferRegs + 21)
		STS		(timerval + 21),r16

		LDS		r16,(servoBufferRegs + 22)
		STS		(timerval + 22),r16

		LDS		r16,(servoBufferRegs + 23)
		STS		(timerval + 23),r16

		LDS		r16,(servoBufferRegs + 24)
		STS		(timerval + 24),r16

		LDS		r16,(servoBufferRegs + 25)
		STS		(timerval + 25),r16

		LDS		r16,(servoBufferRegs + 26)
		STS		(timerval + 26),r16

		LDS		r16,(servoBufferRegs + 27)
		STS		(timerval + 27),r16

		LDS		r16,(servoBufferRegs + 28)
		STS		(timerval + 28),r16

		LDS		r16,(servoBufferRegs + 29)
		STS		(timerval + 29),r16

		LDS		r16,(servoBufferRegs + 30)
		STS		(timerval + 30),r16

		LDS		r16,(servoBufferRegs + 31)
		STS		(timerval + 31),r16

		LDS		r16,(servoBufferRegs + 32)
		STS		(timerval + 32),r16

		LDS		r16,(servoBufferRegs + 33)
		STS		(timerval + 33),r16

		LDS		r16,(servoBufferRegs + 34)
		STS		(timerval + 34),r16

		LDS		r16,(servoBufferRegs + 35)
		STS		(timerval + 35),r16

		LDS		r16,(servoBufferRegs + 36)
		STS		(timerval + 36),r16

		LDS		r16,(servoBufferRegs + 37)
		STS		(timerval + 37),r16

		LDS		r16,(servoBufferRegs + 38)
		STS		(timerval + 38),r16

		LDS		r16,(servoBufferRegs + 39)
		STS		(timerval + 39),r16

		LDS		r16,(servoBufferRegs + 40)
		STS		(timerval + 40),r16

		LDS		r16,(servoBufferRegs + 41)
		STS		(timerval + 41),r16

		LDS		r16,(servoBufferRegs + 42)
		STS		(timerval + 42),r16

		LDS		r16,(servoBufferRegs + 43)
		STS		(timerval + 43),r16

		LDS		r16,(servoBufferRegs + 44)
		STS		(timerval + 44),r16

		LDS		r16,(servoBufferRegs + 45)
		STS		(timerval + 45),r16

		LDS		r16,(servoBufferRegs + 46)
		STS		(timerval + 46),r16

		LDS		r16,(servoBufferRegs + 47)
		STS		(timerval + 47),r16
			
		ret
