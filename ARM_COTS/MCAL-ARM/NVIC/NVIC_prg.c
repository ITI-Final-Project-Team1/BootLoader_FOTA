/*
 * NVIC_prg.c
 *
 *  Created on: Nov 3, 2022
 *      Author: Magdy Adel
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "NVIC_int.h"
#include "NVIC_pvt.h"
#include "NVIC_cfg.h"



void MCAL_NVIC_vEnableInterrupt(u8 A_u8IntID)
{
	if( A_u8IntID <= 31 )
		NVIC_ISER0 = ( 1<<A_u8IntID );
	else if(A_u8IntID<=63 )
		NVIC_ISER1 = ( 1<<(A_u8IntID-32) );
	else if( A_u8IntID<=80 )
		NVIC_ISER2 = ( 1<<(A_u8IntID-64) );
	else{}
		//return Error;
}

void MCAL_NVIC_vDisableInterrupt(u8 A_u8IntID)
{
	if(A_u8IntID<=31 )
		NVIC_ICER0 = ( 1<<A_u8IntID );
	else if(A_u8IntID<=63 )
		NVIC_ICER1 = ( 1<<(A_u8IntID-32) );
	else if( A_u8IntID<=80 )
		NVIC_ICER2 = ( 1<<(A_u8IntID-64) );
	else{}
		//return Error;
}

void MCAL_NVIC_vSetPendingFlag(u8 A_u8IntID)
{
	if( A_u8IntID<=31 )
		NVIC_ISPR0 = ( 1<<A_u8IntID );
	else if(A_u8IntID<=63 )
		NVIC_ISPR1 = ( 1<<(A_u8IntID-32) );
	else if( A_u8IntID<=80 )
		NVIC_ISPR2 = ( 1<<(A_u8IntID-64) );
	else{}
		//return Error;
}

void MCAL_NVIC_vClearPendingFlag(u8 A_u8IntID)
{
	if( A_u8IntID<=31 )
		NVIC_ICPR0 = ( 1<<A_u8IntID );
	else if(A_u8IntID<=63 )
		NVIC_ICPR1 = ( 1<<(A_u8IntID-32) );
	else if( A_u8IntID<=80 )
		NVIC_ICPR2 = ( 1<<(A_u8IntID-64) );
	else{}
		//return Error;
}

u8 MCAL_NVIC_u8GetActiveFlag(u8 A_u8IntID)
{
	u8 val = 0;
	if( A_u8IntID<=31 )
		val = GET_BIT(NVIC_IABR0,A_u8IntID );
	else if(A_u8IntID<=63 )
		val = GET_BIT(NVIC_IABR1,A_u8IntID-32 );
	else if( A_u8IntID<=80 )
		val = GET_BIT(NVIC_IABR2,A_u8IntID-32 );
	else{}
		//return Error;
	return val;
}


void MCAL_NVIC_vSetPriority(s8 A_s8IntID, u8 A_u8GroupPriority, u8 A_u8Group_SubPriority)
{
	/* Equation Masking for number of groups & sub at IPR */
	u8 L_u8Priority = A_u8Group_SubPriority | (A_u8GroupPriority<<A_u8Group_SubPriority );

	/* Core Peripheral */
	if (A_s8IntID < 0) {}

	/* External Peripheral */
	if (A_s8IntID >= 0)
		NVIC_IPR[A_s8IntID] = L_u8Priority << 4;	//Priority Value for interrupt at four MSB

	SCB_AIRCR = (NVIC_GROUP_SUB + (A_u8Group_SubPriority*256) ) ;	// masking number of groups & sub at SCB

}
