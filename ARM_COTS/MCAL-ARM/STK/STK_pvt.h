/*
 * STK_pvt.h
 *
 *  Created on: Nov 6, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_STK_STK_PVT_H_
#define MCAL_ARM_STK_STK_PVT_H_



/* Register Definitions for SysTick */
#define STK_BASE					0xE000E010UL

typedef struct{
	volatile u32 CTRL	;
	volatile u32 LOAD	;
	volatile u32 VAL	;
	volatile u32 CALIB	;
}STK_TypeDef;

#define STK							((STK_TypeDef*)0xE000E010)



//CTRL Bits
#define CTRL_COUNTFLAG				16
#define CTRL_CLKSOURCE				2
#define CTRL_TICKINT				1
#define CTRL_ENABLE					0


#endif /* MCAL_ARM_STK_STK_PVT_H_ */
