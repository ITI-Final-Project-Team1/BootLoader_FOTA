/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : RCC  				******************/
/*************	 Date    : 12 Oct. 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/

#ifndef RCC_RCC_CFG_H_
#define RCC_RCC_CFG_H_


/*
 * choose these options only for RCC_CLOCK_TYPE :
 * - RCC_HSI
 * - RCC_HSE
 * - RCC_PLL
 */

#define RCC_CLOCK_TYPE				RCC_HSE

#if RCC_CLOCK_TYPE == RCC_HSI
	/*
	 * choose these options only :
	 * ENABLED
	 * DISABLED
	 */
	#define RCC_HSI_TRIM_ENABLE		ENABLED

    #if RCC_HSI_TRIM_ENABLE	== DISABLED
	/*
	 * The default value is 16, which, when added to the HSICAL value, should trim the HSI to 8
	 * MHz � 1%. The trimming step is around 40 kHz between two consecutive HSICAL steps.
	 */
	#define RCC_HSI_TRIM_VALUE    	16
	#endif


#elif RCC_CLOCK_TYPE == RCC_HSE
	/*
	 * choose these options only for RCC_HSE_BYPASS :
	 * - BYPASSED 		// means that external 4-16 MHz oscillator bypassed with external clock
	 * - NOT_BYPASSED	// means that external 4-16 MHz oscillator not bypassed
	 */
    #define RCC_HSE_BYPASS			NOT_BYPASSED


#elif RCC_CLOCK_TYPE == RCC_PLL

	/*
	 * choose these options only for RCC_CLOCK_TYPE :
	 * - RCC_PLL_HSI_BY_2
	 * - RCC_PLL_HSE_BY_2
	 * - RCC_PLL_HSE
	 */
	#define RCC_PLL_TYPE 			RCC_PLL_HSE

	/*
	 * choose from value 0 (PLL input clock x 2) to 16 (PLL input clock x 16)
	 * note : both values 1110 and 1111 give us -> PLL input clock x 16
	 *
	 * /////////////// Caution: The PLL output frequency must not exceed 72 MHz ///////////////
	 *
	 */
	#define RCC_PLL_MUL				0b0000


#endif



/*
 * choose these options only :
 * ENABLED
 * DISABLED
 */
#define RCC_CSS_ENABLE					DISABLED


/*
 * choose these options only :
 * ENABLED
 * DISABLED
 */
#define RCC_MCO_ENABLE					DISABLED

#if RCC_MCO_ENABLE == ENABLED
	/*
	 * choose these options only :
	 * - MCO_SYSCLK
	 * - MCO_HSI_CLOCK
	 * - MCO_HSE_CLOCK
	 * - MCO_PLL_CLOCK_BY_2
	 * note : When the System Clock is selected to output to the MCO pin, make sure that this clock
	 * does not exceed 50 MHz (the maximum IO speed).
	 */
	#define RCC_MCO_CLOCK				MCO_SYSCLK
#endif


/*
 * choose these options only :
 * - SYSCLK_HSI
 * - SYSCLK_HSE
 * - SYSCLK_PLL
 */
#define RCC_SYSCLK						SYSCLK_HSE

/*
 * choose these options only :
 * - AHB_NO_CLOCK
 * - AHB_BY_2
 * - AHB_BY_4
 * - AHB_BY_8
 * - AHB_BY_16
 * - AHB_BY_64
 * - AHB_BY_128
 * - AHB_BY_256
 * - AHB_BY_512
 *
 */
#define RCC_AHB_PRESCALER				AHB_NO_CLOCK

/*
 * choose these options only :
 * - PPRE1_NO_CLOCK
 * - PPRE1_BY_2
 * - PPRE1_BY_4
 * - PPRE1_BY_8
 * - PPRE1_BY_16
 */
#define RCC_APB1_PRESCALER				PPRE1_NO_CLOCK

/*
 * choose these options only :
 * - PPRE2_NO_CLOCK
 * - PPRE2_BY_2
 * - PPRE2_BY_4
 * - PPRE2_BY_8
 * - PPRE2_BY_16
 */
#define RCC_APB2_PRESCALER				PPRE2_NO_CLOCK



#endif /* RCC_RCC_CFG_H_ */
