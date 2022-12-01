/*
 * GPIO_prg.c
 *
 *  Created on: Nov 2, 2022
 *      Author: Magdy Adel
 */

//---------------------------------------------------------
//Includes
//---------------------------------------------------------
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../RCC/RCC_int.h"
#include "GPIO_int.h"
#include "GPIO_pvt.h"
#include "GPIO_cfg.h"


//---------------------------------------------------------
//Static Functions
//---------------------------------------------------------
static u8 Get_CRLH_Position(u16 PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}


/*
 *=======================================================================
 *						APIS FUNCTIONS Implementations
 *=======================================================================
 *
*/
void MCAL_GPIO_vInit(GPIOxHandle_t GPIOx , GPIO_PinConfig_t *PinConfig)
{
	//Port configuration register low (GPIOx_CRL) Configure PINS from 0 till 7
	//Port configuration register low (GPIOx_CRh) Configure PINS from 8 till 15
	volatile u32 * configregister = NULL;
	u8 PIN_Config =0;

	configregister =(PinConfig-> GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL:&GPIOx->CRH;

	//clear MODEy[1:0] CNFy[1:0]
	(*configregister) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	//if Pin is output
	if( (PinConfig->GPIO_MODE==GPIO_Mode_AF_OUT_OpenDrain)
			||(PinConfig->GPIO_MODE==GPIO_Mode_AF_OUT_PushPull)
			||(PinConfig->GPIO_MODE==GPIO_Mode_OUT_OpenDrain)
			||(PinConfig->GPIO_MODE==GPIO_Mode_OUT_PushPull) )
	{
		//Set  CNFy[1:0] MODEy[1:0]
		PIN_Config =( (( (PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_OUTPUT_SPEED) ) &0x0f) ;
		(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
	}
	//if Pin is input
	else //MODE= 00: Input mode (reset state)
	{
		if( (PinConfig->GPIO_MODE == GPIO_Mode_IN_Floating )
				|| (PinConfig->GPIO_MODE==GPIO_MODE_Analog) )
		{
			//Set  CNFy[1:0] MODEy[1:0]00
			PIN_Config =( (((PinConfig->GPIO_MODE ) << 2) | 0x0) &0x0f) ;
		}
		else if (PinConfig->GPIO_MODE == GPIO_MODE_AF_IN) //Consider it as input floating
		{
			PIN_Config =( ( ( (GPIO_Mode_IN_Floating) << 2) | 0x0) &0x0f) ;
		}
		else //PU PD Input
		{
			PIN_Config =( (((GPIO_Mode_IN_PullUp ) << 2) | 0x0) &0x0f) ;
			if( (PinConfig->GPIO_MODE == GPIO_Mode_IN_PullUp) )
			{
				//PxODR=1 Input pull-up :Table 20. Port bit configuration table
				GPIOx->ODR |= PinConfig->GPIO_PinNumber ;
			}
			else
			{
				//PxODR=0 Input pull-up :Table 20. Port bit configuration table
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber) ;
			}
		}
	}
	//write on the CRL or CRH
	(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}

void MCAL_GPIO_vDeInit(GPIOxHandle_t GPIOx)
{
	//APB2 peripheral reset register (RCC_APB2RSTR)
	//Set and cleared by software.
	if(GPIOx == GPIOA)
	{
		RCC_vRESET( IOPA_APB2, APB2);

	}else if(GPIOx==GPIOB)
	{
		RCC_vRESET( IOPB_APB2, APB2);
	}else if(GPIOx==GPIOC)
	{
		RCC_vRESET( IOPC_APB2, APB2);

	}else if(GPIOx==GPIOD)
	{
		RCC_vRESET( IOPD_APB2, APB2);

	}else  if(GPIOx==GPIOE)
	{
		RCC_vRESET( IOPE_APB2 ,APB2);

	}
}

u8 MCAL_GPIO_u8ReadPin(GPIOxHandle_t GPIOx , u16 PinNumber)
{
	u8 bitstatus=0;
	if( ( GPIOx->IDR & PinNumber ) != GPIO_PIN_LOW)
	{
		bitstatus =GPIO_PIN_HIGH;
	}else
	{
		bitstatus =GPIO_PIN_LOW;
	}
	return bitstatus;
}

u16 MCAL_GPIO_u16ReadPort(GPIOxHandle_t GPIOx )
{
	u16 portValue;
	portValue = (u16)GPIOx->IDR ;
	return portValue;
}

void MCAL_GPIO_vWritePin(GPIOxHandle_t GPIOx , u16 PinNumber, GPIOPinStatus_t Value)
{
	if( Value != GPIO_PIN_LOW)
	{
		//GPIOx->ODR |= PinNumber;
		//or
		GPIOx->BSRR |= (u32)PinNumber;

	}else
	{
		GPIOx->BRR |= (u32)PinNumber;
	}
}


void MCAL_GPIO_vWritePort(GPIOxHandle_t GPIOx , u16 Value)
{
	GPIOx->ODR = Value;
}

void MCAL_GPIO_vTogglePin(GPIOxHandle_t GPIOx , u16 PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}

GPIO_ErrorStatusType  MCAL_GPIO_enuLockPin(GPIOxHandle_t GPIOx , u16 PinNumber)
{
	/*Bit 16 LCKK[16]: Lock key
		This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
		0: Port configuration lock key not active
		1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
		LOCK key writing sequence:
		Write 1
		Write 0
		Write 1
		Read 0
		Read 1 (this read is optional but confirms that the lock is active)
		Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
		Any error in the lock sequence will abort the lock.
		Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
		These bits are read write but can only be written when the LCKK bit is 0.
		0: Port configuration not locked
		1: Port configuration locked.*/
		volatile u32 tmp=1<<16;
		//set the LCKy
		tmp |=PinNumber;

		//Write 1
		GPIOx->LCKR =tmp;

		//Write 0
		GPIOx->LCKR =PinNumber;

		//Write 1
		GPIOx->LCKR =tmp;

		//Read 0
		tmp =GPIOx->LCKR;
		//Read 1 (this read is optional but confirms that the lock is active)
		if((u32)(GPIOx->LCKR & 1<<16))
		{
			return GPIO_RETURN_LOCK_EN;

		}else
		{
			return GPIO_RETURN_LOCK_ERROR;
		}

}

