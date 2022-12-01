/*
 * STK_int.h
 *
 *  Created on: Nov 6, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_STK_STK_INT_H_
#define MCAL_ARM_STK_STK_INT_H_

#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif


//=======================================================================
//Configuration References
//=======================================================================

/* Clock source selection */
typedef enum{
	STK_SRC_AHB	=0,
	STK_SRC_AHB_DivBy_8
}CLKSOURCE_t;

/* Define variable for interval mode */
typedef enum{
	STK_SINGLE_INTERVAL	=0,
	STK_PERIODIC_INTERVAL
}InetrvalMODE_t;
//=======================================================================



/*
 *=======================================================================
 *						APIS FUNCTIONS Definitions
 *=======================================================================
 *
*/
void MCAL_STK_voidInit				  (CLKSOURCE_t clkSrc);
void MCAL_STK_voidSetBusyWait		  (u32 A_u32Ticks);
void MCAL_STK_voidSetIntervalSingle	  (u32 A_u32Ticks, void (*fptr) (void));
void MCAL_STK_voidSetIntervalPeriodic (u32 A_u32Ticks, void (*fptr) (void));
void MCAL_STK_voidStopInterval		  (void);
u32  MCAL_STK_u32GetElapsedTime		  (void);
u32  MCAL_STK_u32GetRemainingTime     (void);


//=======================================================================



#ifdef __cplusplus
}
#endif

#endif /* MCAL_ARM_STK_STK_INT_H_ */
