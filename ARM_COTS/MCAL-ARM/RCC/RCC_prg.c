#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "RCC_int.h"
#include "RCC_pvt.h"
#include "RCC_cfg.h"

/*********************************************



  _____     _____    _____     _____    _____    _____  __      __  ______   _____
 |  __ \   / ____|  / ____|   |  __ \  |  __ \  |_   _| \ \    / / |  ____| |  __ \
 | |__) | | |      | |        | |  | | | |__) |   | |    \ \  / /  | |__    | |__) |
 |  _  /  | |      | |        | |  | | |  _  /    | |     \ \/ /   |  __|   |  _  /
 | | \ \  | |____  | |____    | |__| | | | \ \   _| |_     \  /    | |____  | | \ \
 |_|  \_\  \_____|  \_____|   |_____/  |_|  \_\ |_____|     \/     |______| |_|  \_\




***********************************************/


void RCC_vInit(void)
{
	#if RCC_CLOCK_TYPE == RCC_HSI
		// HSI Trim
		#if RCC_HSI_TRIM_ENABLE	== ENABLED
			RCC->CR &= ~(HSITRIM_MASK);
			RCC->CR |= (RCC_HSI_TRIM_VALUE<<3);
		#endif

		while(!(GET_BIT(RCC->CR, CR_HSIRDY)))
		{
			//wait until internal 8 MHz RC oscillator is ready
		}
		// internal 8 MHz RC oscillator ON
		SET_BIT(RCC->CR, CR_HSION);

	#elif RCC_CLOCK_TYPE == RCC_HSE
		// HSI Bypass
		#if RCC_HSE_BYPASS == BYPASSED
			SET_BIT(RCC->CR, CR_HSEBYP);
		#elif RCC_HSE_BYPASS == NOT_BYPASSED
			CLEAR_BIT(RCC->CR, CR_HSEBYP);
		#else
			#error "you chose wrong RCC_HSE_BYPASS option"
		#endif

		while(!(GET_BIT(RCC->CR, CR_HSERDY)))
		{
			//wait until HSE oscillator ready is ready
		}
		// HSE oscillator ON
		SET_BIT(RCC->CR, CR_HSEON);

	#elif RCC_CLOCK_TYPE == RCC_PLL
		// Disable the PLL to write its configuration first then activate it
		CLEAR_BIT(RCC->CR, CR_PLLON);
		// PLL Source : HSE, HSE/2, HSI/2
		#if RCC_PLL_TYPE == RCC_PLL_HSI_BY_2
			CLEAR_BIT(RCC->CFGR, CFGR_PLLSRC);
		#elif RCC_PLL_TYPE == RCC_PLL_HSE_BY_2
			SET_BIT(RCC->CFGR, CFGR_PLLSRC);
			SET_BIT(RCC->CFGR, CFGR_PLLXTPRE);
		#elif RCC_PLL_TYPE == RCC_PLL_HSE
			SET_BIT(RCC->CFGR, CFGR_PLLSRC);
			CLEAR_BIT(RCC->CFGR, CFGR_PLLXTPRE);
		#endif
		// PLL Multiplier
		RCC->CFGR &= ~(PLLMUL_MASK);
		RCC->CFGR |= (RCC_PLL_MUL<<18);
		// PLL ON
		SET_BIT(RCC->CR, CR_PLLON);
	#else
		#error "you chose wrong RCC_CLOCK_TYPE option"
	#endif

	/*Other configurations*/
	// CSS
	#if RCC_CSS_ENABLE == ENABLED
		SET_BIT(RCC->CR, CR_CSSON);
	#elif RCC_CSS_ENABLE == DISABLED
		CLEAR_BIT(RCC->CR, CR_CSSON);
	#else
		#error "you chose wrong CSS_ENABLE option"
	#endif

	// MCO
	#if RCC_MCO_ENABLE == ENABLED
		RCC->CFGR &= ~(MCO_MASK);
		RCC->CFGR |= (RCC_MCO_CLOCK << 24);
	#elif RCC_MCO_ENABLE == DISABLED
		RCC->CFGR &= ~(MCO_MASK);
		RCC->CFGR |= (MCO_NO_CLOCK << 24);
	#else
		#error "you chose wrong MCO_ENABLE option"
	#endif

	/* AHB, APB1, APB2 prescalers */
	RCC->CFGR &= ~(AHB_PRESCALER_MASK);
	RCC->CFGR |= (RCC_AHB_PRESCALER << 4);

	RCC->CFGR &= ~(APB1_PRESCALER_MASK);
	RCC->CFGR |= (RCC_APB1_PRESCALER<< 8);

	RCC->CFGR &= ~(APB2_PRESCALER_MASK);
	RCC->CFGR |= (RCC_APB2_PRESCALER << 11);

	/* SYSCLK */
	RCC->CFGR &= ~(SW_MASK);
	RCC->CFGR |= (RCC_SYSCLK << 0);
}



void RCC_vEnableClock(Prepherial_EN_t Copy_prepherial , Bus_ID_t Copy_busId )
{
	switch (Copy_busId)
	{
		case AHB:
			SET_BIT(RCC->AHBENR, Copy_prepherial);
			break;
		case APB1:
			SET_BIT(RCC->APB1ENR, Copy_prepherial);
			break;
		case APB2:
			SET_BIT(RCC->APB2ENR, Copy_prepherial);
			break;
		default:
			break;
	}
}


void RCC_vDisableClock(Prepherial_EN_t Copy_prepherial , Bus_ID_t Copy_busId )
{
	switch (Copy_busId)
	{
		case AHB:
			CLEAR_BIT(RCC->AHBENR, Copy_prepherial);
			break;
		case APB1:
			CLEAR_BIT(RCC->APB1ENR, Copy_prepherial);
			break;
		case APB2:
			CLEAR_BIT(RCC->APB2ENR, Copy_prepherial);
			break;
		default:
			/* Error */
			break;
	}
}


void RCC_vSetSysClock(System_Clock_t Copy_systemClock)
{
	switch (Copy_systemClock)
	{
		case HSE:
			RCC->CFGR &= ~(SW_MASK);
			RCC->CFGR |= (SYSCLK_HSE << 0);
			break;
		case HSI:
			RCC->CFGR &= ~(SW_MASK);
			RCC->CFGR |= (SYSCLK_HSI << 0);
			break;
		case PLL:
			RCC->CFGR &= ~(SW_MASK);
			RCC->CFGR |= (SYSCLK_PLL << 0);
			break;
		default:
			/* Error */
			break;
	}
}




void RCC_vRESET(Prepherial_EN_t Copy_prepherial , Bus_ID_t Copy_busId )
{
	if(A_u16PeripheralID <= 31)
		{
			switch (A_u8BusID)
			{
				case RCC_AHB  : break;
				case RCC_APB1 : SET_BIT(RCC->APB1RSTR,A_u16PeripheralID);
					break;
				case RCC_APB2 : SET_BIT(RCC->APB2RSTR,A_u16PeripheralID);
					break;
				//default       : /* return Error ; */ break;
			}
		}else{/* return Error ; */}
}

void RCC_vDisableAllInterrupt(void)
{
	/* Disable all interrupts and clear pending bits  */
	RCC->CIR = 0x009F0000;
}
void RCC_vEnHSIInterrupt(void)
{
	/* Enable HSI interrupts and clear pending bits  */
	RCC->CIR = 0x009F1F00;
}
