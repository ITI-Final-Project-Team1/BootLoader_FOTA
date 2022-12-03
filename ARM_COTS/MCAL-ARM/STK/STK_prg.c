/*
 * STK_prg.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Magdy Adel
 */

//---------------------------------------------------------
//Includes
//---------------------------------------------------------
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../RCC/RCC_int.h"
#include "STK_int.h"
#include "STK_pvt.h"
#include "STK_cfg.h"
//==========================================================


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
u8 singleFlag = 0;
void (*GP_STK_Callback)(void) = NULL;
//=======================================================================


//---------------------------------------------------------
//Static Functions
//---------------------------------------------------------

//==========================================================


/*
 *=======================================================================
 *						APIS FUNCTIONS Implementations
 *=======================================================================
 *
*/
void MCAL_STK_vInit (CLKSOURCE_t clkSrc)
{
	/*Apply clock choice from config file*/
	STK->CTRL = (clkSrc << CTRL_CLKSOURCE);
	/* Disable Interrupt for SysTick */
	CLR_BIT(STK->CTRL, CTRL_TICKINT);
	/* Disable SysTick */
	CLR_BIT(STK->CTRL, CTRL_ENABLE);

}
void MCAL_STK_vSetBusyWait(u32 A_u32Ticks)
{
	/* CLEAR Timer VAL register */
	STK->VAL = 0;
	/* SaveTicks at LOAD Register */
	STK->LOAD = A_u32Ticks ;
	/* Disable Interrupt for SysTick */
	CLR_BIT(STK->CTRL,CTRL_TICKINT);
	/* Enable SysTick */
	SET_BIT(STK->CTRL,CTRL_ENABLE);

	/* wait until flag == 0 */
	while( GET_BIT(STK->CTRL,CTRL_COUNTFLAG)==0 );

	/* Stop timer and Clear COUNTFLAG */
	CLR_BIT(STK->CTRL, CTRL_ENABLE);
	STK->VAL = 0;


}
void MCAL_STK_vSetIntervalSingle(u32 A_u32Ticks, void (*fptr) (void))
{
	/* Set single flag */
	singleFlag = 1;

	/* register the Callback function */
	GP_STK_Callback=fptr;

	/* CLEAR Timer VAL register */
	STK->VAL = 0;

	/* Enable Interrupt for SysTick */
	SET_BIT(STK->CTRL,CTRL_TICKINT);

	/* SaveTicks at LOAD Register */
	STK->LOAD = A_u32Ticks ;

	/* Start Timer --Enable SysTick */
	SET_BIT(STK->CTRL,CTRL_ENABLE);

}

void MCAL_STK_vSetIntervalPeriodic(u32 A_u32Ticks, void (*fptr) (void))
{
	/* Clear single flag */
	singleFlag = 0;

	/* register the Callback function */
	GP_STK_Callback=fptr;

	/* CLEAR Timer VAL register */
	STK->VAL = 0;

	/* Enable Interrupt for SysTick */
	SET_BIT(STK->CTRL,CTRL_TICKINT);

	/* SaveTicks at LOAD Register */
	STK->LOAD = A_u32Ticks ;

	/* Start Timer --Enable SysTick */
	SET_BIT(STK->CTRL,CTRL_ENABLE);


}
void MCAL_STK_vStopInterval(void)
{
	/* Stop timer  */
	CLR_BIT(STK->CTRL, CTRL_ENABLE);
}

u32  MCAL_STK_u32GetElapsedTime(void)
{
	return (STK->LOAD - STK->VAL);
}

u32  MCAL_STK_u32GetRemainingTime(void)
{
	return STK->VAL;
}

void MCAL_STK_delay_ms( u32 Copy_u32Time )
{
	MCAL_STK_vSetBusyWait(Copy_u32Time*1000);
}
void MCAL_STK_delay_us( u32 Copy_u32Time )
{
	MCAL_STK_vSetBusyWait(Copy_u32Time);
}
//=======================================================================


/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void SysTick_Handler (void)
{

	//Call STK_CallBack
	if(GP_STK_Callback!=NULL)
	{
		if(singleFlag==1)
		{
			singleFlag = 0;
			STK->VAL = 0;
			CLR_BIT(STK->CTRL, CTRL_ENABLE); //ENABLE BIT
		}
		GP_STK_Callback();
	}
}

//=======================================================================

