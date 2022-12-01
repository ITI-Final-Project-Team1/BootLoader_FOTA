/*
 * EXTI_prg.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Magdy Adel
 */

/*
 *=======================================================================
 *						Geniric INCLUDES
 *=======================================================================
 *
*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../NVIC/NVIC_int.h"
#include "../GPIO/GPIO_int.h"
#include "../AFIO/AFIO_int.h"
#include "EXTI_int.h"
#include "EXTI_pvt.h"
#include "EXTI_cfg.h"
//=======================================================================




/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
typedef void (*Exti_Callback_t)(void);
static Exti_Callback_t SPtr_IRQ_CallBack[16] ;
//=======================================================================


/*
 *=======================================================================
 *						GENERIC FUNCTIONS
 *=======================================================================
 *
*/

static void EXTI_Update (EXTI_PinCFGHandle EXTI_cfg)
{
	//1- Configure GPIO to be AF Input -->Floating INPUT
	GPIO_PinConfig_t PinCfg ;
	//Update the GPIO Pin to be Floating INPUT
	PinCfg.GPIO_PinNumber = EXTI_cfg->EXTI_PIN.GPIO_PIN;
	PinCfg.GPIO_MODE = GPIO_Mode_IN_Floating;
	MCAL_GPIO_vInit(EXTI_cfg->EXTI_PIN.GPIO_Port, &PinCfg);

	//2- UPDATE AFIO to Route between EXTI Line with PORT A,B,C,D
	MCAL_AFIO_vSetEXTIConfig(EXTI_cfg->EXTI_PIN.GPIO_Port ,EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber);
	//=====================================================

	//3- Update Rising or falling Register
	EXTI->RTSR &= ~(1 << EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber);

	if(EXTI_cfg->Trigger_Case == EXTI_Trigger_RISING)
	{
		EXTI->RTSR |= (1 << EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber );

	}else if(EXTI_cfg->Trigger_Case == EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |= (1 << EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber);

	}else if(EXTI_cfg->Trigger_Case == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= (1 << EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber);
		EXTI->FTSR |= (1 << EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber);

	}
	//=====================================================


	//4- Update IRQ Handling CallBack

	SPtr_IRQ_CallBack[EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber] =EXTI_cfg->Ptr_IRQ_CallBack;
	//=====================================================


	//5- Enable/Disable IRQ EXTI & NVIC

	if(EXTI_cfg->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<<EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber) ;
		MCAL_NVIC_vEnableInterrupt( EXTI_cfg->EXTI_PIN.IVT_IRQ_Number );
	}else
	{
		EXTI->IMR &= ~(1<<EXTI_cfg->EXTI_PIN.EXTI_InputLineNumber) ;
		MCAL_NVIC_vDisableInterrupt(EXTI_cfg->EXTI_PIN.IVT_IRQ_Number);
	}
	//=====================================================
}

//=======================================================================



/*
 *=======================================================================
 *						APIS FUNCTIONS Implementations
 *=======================================================================
 *
*/

void MCAL_EXTI_vInit(EXTI_PinCFGHandle EXTI_cfg)
{
	EXTI_Update(EXTI_cfg);

}

void MCAL_EXTI_vDeInit_AllGPIO (void)
{
	EXTI->IMR = 	0x00000000 ;
	EXTI->EMR = 	0x00000000 ;
	EXTI->RTSR = 	0x00000000 ;
	EXTI->FTSR =	0x00000000 ;
	EXTI->SWIER = 	0x00000000 ;
	EXTI->PR = 		0xFFFFFFFF ; //rc_w1 cleared by writing a '1' into the PR

	//Disable EXTI IRQ from NVIC
	MCAL_NVIC_vDisableInterrupt(NVIC_EXTI0_IRQ);
	MCAL_NVIC_vDisableInterrupt(NVIC_EXTI1_IRQ);
	MCAL_NVIC_vDisableInterrupt(NVIC_EXTI2_IRQ);
	MCAL_NVIC_vDisableInterrupt(NVIC_EXTI3_IRQ);
	MCAL_NVIC_vDisableInterrupt(NVIC_EXTI4_IRQ);
	MCAL_NVIC_vDisableInterrupt(NVIC_EXTI5_9_IRQ);
	MCAL_NVIC_vDisableInterrupt(NVIC_EXTI10_15_IRQ);

}


void MCAL_EXTI_vUpdate(EXTI_PinCFGHandle EXTI_cfg)
{
	EXTI_Update(EXTI_cfg);
}


void MCAL_EXTI_vTriggerSwInterrupt(EXTI_LineNum_t A_xLineId)
{
	SET_BIT(EXTI->SWIER, A_xLineId );
}
//=======================================================================


/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void EXTI0_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<0 ;
	//Call IRQ_CallBack
	SPtr_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<1 ;
	//Call IRQ_CallBack
	SPtr_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<2 ;
	//Call IRQ_CallBack
	SPtr_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<3 ;
	//Call IRQ_CallBack
	SPtr_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler (void)
{
	//clear pending register for specific EXTI line (clear by writing 1)
	EXTI->PR |= 1<<4 ;
	//Call IRQ_CallBack
	SPtr_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler (void)
{
	if(EXTI->PR & 1 << 5) { EXTI->PR |= (1 << 5) ; SPtr_IRQ_CallBack[5]() ; }
	if(EXTI->PR & 1 << 6) { EXTI->PR |= (1 << 6) ; SPtr_IRQ_CallBack[6]() ; }
	if(EXTI->PR & 1 << 7) { EXTI->PR |= (1 << 7) ; SPtr_IRQ_CallBack[7]() ; }
	if(EXTI->PR & 1 << 8) { EXTI->PR |= (1 << 8) ; SPtr_IRQ_CallBack[8]() ; }
	if(EXTI->PR & 1 << 9) { EXTI->PR |= (1 << 9) ; SPtr_IRQ_CallBack[9]() ; }
}

void EXTI15_10_IRQHandler (void)
{
	if(EXTI->PR & 1 << 10) { EXTI->PR |= (1 << 10) ; SPtr_IRQ_CallBack[10]() ; }
	if(EXTI->PR & 1 << 11) { EXTI->PR |= (1 << 11) ; SPtr_IRQ_CallBack[11]() ; }
	if(EXTI->PR & 1 << 12) { EXTI->PR |= (1 << 12) ; SPtr_IRQ_CallBack[12]() ; }
	if(EXTI->PR & 1 << 13) { EXTI->PR |= (1 << 13) ; SPtr_IRQ_CallBack[13]() ; }
	if(EXTI->PR & 1 << 14) { EXTI->PR |= (1 << 14) ; SPtr_IRQ_CallBack[14]() ; }
	if(EXTI->PR & 1 << 15) { EXTI->PR |= (1 << 15) ; SPtr_IRQ_CallBack[15]() ; }
}
//=======================================================================



