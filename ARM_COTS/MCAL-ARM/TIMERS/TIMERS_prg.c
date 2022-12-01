/*
 * TIMERS_prg.c
 *
 *  Created on: Nov 17, 2022
 *      Author: Magdy Adel
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../RCC/RCC_int.h"
#include "TIMERS_int.h"
#include "TIMERS_pvt.h"



void MCAL_TIMERx_vInit(TIMERx_t timer, TIMERx_Cfg_t * timerCFG)
{
	u16 tmpcr1 = 0;
	TIMx_TypeDef* TIMx =NULL;
	switch (timer) {
		case TIMER1: TIMx=TIM1; break;
		case TIMER2: TIMx=TIM2; break;
		case TIMER3: TIMx=TIM3; break;
		case TIMER4: TIMx=TIM4; break;
		case TIMER5: TIMx=TIM5; break;
	}

	tmpcr1 = TIMx->CR1;

	/* Select the Counter Mode */
	tmpcr1 &= (u16)(~((u16)(0x0010 | 0x0060)));
	tmpcr1 |= (u32)timerCFG->CounterMode;


	TIMx->CR1 = tmpcr1;

	/* Set the Preload value */
	TIMx->ARR = timerCFG->Period ;

	/* Set the Prescaler value */
	TIMx->PSC = timerCFG->Prescaler;


	/* Generate an update event to reload the Prescaler and the Repetition counter
	 values immediately */
	TIMx->EGR = (u16)0x0001;
}


void MCAL_TIMERx_vDeInit(TIMERx_t timer)
{
	//APB1 peripheral reset register (RCC_APB1RSTR)
	//Set and cleared by software.
	switch (timer)
	{
		case TIMER1: MCAL_RCC_vRESET( RCC_TIM1_APB2, RCC_APB2); break;
		case TIMER2: MCAL_RCC_vRESET( RCC_TIM2_APB1, RCC_APB1); break;
		case TIMER3: MCAL_RCC_vRESET( RCC_TIM3_APB1, RCC_APB1); break;
		case TIMER4: MCAL_RCC_vRESET( RCC_TIM4_APB1, RCC_APB1); break;
		case TIMER5: MCAL_RCC_vRESET( RCC_TIM5_APB1, RCC_APB1); break;
	}

}


/**
  * @brief  Enables the specified TIM peripheral.
  * @param  TIMx: where x can be 1 to 17 to select the TIMx peripheral.
  * @param  NewState: new state of the TIMx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCAL_TIMERx_vStart(TIMERx_t timer)
{
	TIMx_TypeDef* TIMx =NULL;
	switch (timer) {
		case TIMER1: TIMx=TIM1; break;
		case TIMER2: TIMx=TIM2; break;
		case TIMER3: TIMx=TIM3; break;
		case TIMER4: TIMx=TIM4; break;
		case TIMER5: TIMx=TIM5; break;
	}

    /* Enable the TIM Counter */
	//SET_BIT(TIMx->CR1, )
    TIMx->CR1 |= TIM_CR1_CEN;

}

void MCAL_TIMERx_vStop(TIMERx_t timer)
{
	TIMx_TypeDef* TIMx =NULL;
	switch (timer) {
		case TIMER1: TIMx=TIM1; break;
		case TIMER2: TIMx=TIM2; break;
		case TIMER3: TIMx=TIM3; break;
		case TIMER4: TIMx=TIM4; break;
		case TIMER5: TIMx=TIM5; break;
	}

	/* Disable the TIM Counter */
	TIMx->CR1 &= (u16)(~((u16)TIM_CR1_CEN));

}


/**
  * @brief  Initializes the TIMx Channel1 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be  1 to 17 except 6 and 7 to select the TIM peripheral.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM peripheral.
  * @retval None
  */
void MCAL_TIMERx_OC1Init(TIMERx_t timer, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	TIMx_TypeDef* TIMx = NULL;

	switch (timer) {
		case TIMER1: TIMx=TIM2; break;
		case TIMER2: TIMx=TIM2; break;
		case TIMER3: TIMx=TIM3; break;
		case TIMER4: TIMx=TIM4; break;
		case TIMER5: TIMx=TIM2; break;
	}
	u16 tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

	/* Disable the Channel 1: Reset the CC1E Bit */
	TIMx->CCER &= (u16)(~(u16)0x0001);//TIM_CCER_CC1E);
		/* Get the TIMx CCER register value */
	tmpccer = TIMx->CCER;
	/* Get the TIMx CR2 register value */
	tmpcr2 =  TIMx->CR2;

	/* Get the TIMx CCMR1 register value */
	tmpccmrx = TIMx->CCMR1;

	/* Reset the Output Compare Mode Bits */
	tmpccmrx &= (u16)(~((u16)0x0070));//TIM_CCMR1_OC1M));
	tmpccmrx &= (u16)(~((u16)0x0003));//TIM_CCMR1_CC1S));

	/* Select the Output Compare Mode */
	tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;

	/* Reset the Output Polarity level */
	tmpccer &= (u16)(~((u16)0x0002));//TIM_CCER_CC1P));
	/* Set the Output Compare Polarity */
	tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;

	/* Set the Output State */
	tmpccer |= TIM_OCInitStruct->TIM_OutputState;

	/* Write to TIMx CR2 */
	TIMx->CR2 = tmpcr2;

	/* Write to TIMx CCMR1 */
	TIMx->CCMR1 = tmpccmrx;

	/* Set the Capture Compare Register value */
	TIMx->CCRn[0] = TIM_OCInitStruct->TIM_Pulse;

	/* Write to TIMx CCER */
	TIMx->CCER = tmpccer;
}


/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR1.
  * @param  TIMx: where x can be  1 to 17 except 6 and 7 to select the TIM peripheral.
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TIM_OCPreload_Enable
  *     @arg TIM_OCPreload_Disable
  * @retval None
  */
void MCAL_TIMERx_OC1PreloadConfig(TIMERx_t timer, u16 TIM_OCPreload)
{
	TIMx_TypeDef* TIMx = NULL;
	switch (timer) {
		case TIMER1: TIMx=TIM1; break;
		case TIMER2: TIMx=TIM2; break;
		case TIMER3: TIMx=TIM3; break;
		case TIMER4: TIMx=TIM4; break;
		case TIMER5: TIMx=TIM5; break;
	}
	u16 tmpccmr1 = 0;

	tmpccmr1 = TIMx->CCMR1;
	/* Reset the OC1PE Bit */
	tmpccmr1 &= (u16)~((u16)0x0002);//TIM_CCMR1_OC1PE);
	/* Enable or Disable the Output Compare Preload feature */
	tmpccmr1 |= TIM_OCPreload;
	/* Write to TIMx CCMR1 register */
	TIMx->CCMR1 = tmpccmr1;
}


/**
  * @brief  Sets the TIMx Capture Compare1 Register value
  * @param  TIMx: where x can be 1 to 17 except 6 and 7 to select the TIM peripheral.
  * @param  Compare1: specifies the Capture Compare1 register new value.
  * @retval None
  */
void MCAL_TIMERx_SetCompare1(TIMERx_t timer, u16 CompareVAL1)
{
	TIMx_TypeDef* TIMx = NULL;
	switch (timer) {
		case TIMER1: TIMx=TIM1; break;
		case TIMER2: TIMx=TIM2; break;
		case TIMER3: TIMx=TIM3; break;
		case TIMER4: TIMx=TIM4; break;
		case TIMER5: TIMx=TIM5; break;
	}
	/* Set the Capture Compare1 Register value */
	TIMx->CCRn[0] = CompareVAL1;
}



void dus(u32 us)
{
	TIM2->CNT=0;
	while(TIM2->CNT < us);
}

void dms(u32 ms)
{
	u32 i=0;
	for(i=0;i<ms;i++)
	{
		dus(1000);
	}
}


