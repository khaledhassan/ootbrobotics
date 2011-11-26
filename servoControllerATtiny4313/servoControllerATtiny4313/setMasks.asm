/*
 * setMasks.asm
 *
 *  Created: 11/6/2011 8:53:50 PM
 *   Author: bfc
 */ 
 setMasks:
		//masks 0-7
		LDI		r16,(1<<0)
		STS		(mask + 0),r16

		LDI		r16,(1<<1)
		STS		(mask + 1),r16

		LDI		r16,(1<<2)
		STS		(mask + 2),r16

		LDI		r16,(1<<3)
		STS		(mask + 3),r16

		LDI		r16,(1<<4)
		STS		(mask + 4),r16

		LDI		r16,(1<<5)
		STS		(mask + 5),r16

		LDI		r16,(1<<6)
		STS		(mask + 6),r16

		LDI		r16,(1<<7)
		STS		(mask + 7),r16

		//masks 8-15
		LDI		r16,(1<<0)
		STS		(mask + 8),r16

		LDI		r16,(1<<1)
		STS		(mask + 9),r16

		LDI		r16,(1<<2)
		STS		(mask + 10),r16

		LDI		r16,(1<<3)
		STS		(mask + 11),r16

		LDI		r16,(1<<4)
		STS		(mask + 12),r16

		LDI		r16,(1<<5)
		STS		(mask + 13),r16

		LDI		r16,(1<<6)
		STS		(mask + 14),r16

		LDI		r16,(1<<7)
		STS		(mask + 15),r16

		//masks 16-23
		LDI		r16,(1<<0)
		STS		(mask + 16),r16

		LDI		r16,(1<<1)
		STS		(mask + 17),r16

		LDI		r16,(1<<2)
		STS		(mask + 18),r16

		LDI		r16,(1<<3)
		STS		(mask + 19),r16

		LDI		r16,(1<<4)
		STS		(mask + 20),r16

		LDI		r16,(1<<5)
		STS		(mask + 21),r16

		LDI		r16,(1<<6)
		STS		(mask + 22),r16

		LDI		r16,(1<<7)
		STS		(mask + 23),r16

		ret
