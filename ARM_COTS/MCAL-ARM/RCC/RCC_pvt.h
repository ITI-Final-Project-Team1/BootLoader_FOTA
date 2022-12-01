/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : RCC  				******************/
/*************	 Date    : 12 Oct. 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/
#ifndef RCC_RCC_PVT_H_
#define RCC_RCC_PVT_H_




//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_BASE				0x40021000UL //UL for it constant

typedef struct{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
}RCC_TypeDef;

#define RCC						((RCC_TypeDef *)RCC_BASE)
//-------------------------end-----------------------------


/***************************** RCC_CR bits *****************************/

#define CR_HSION		            0
#define CR_HSIRDY		            1
#define CR_HSEON		            16
#define CR_HSERDY		            17
#define CR_HSEBYP		            18
#define CR_CSSON		            19
#define CR_PLLON		            24
#define CR_PLLRDY		            25


/***************************** RCC_CFGR bits *****************************/

#define CFGR_PLLSRC		            16
#define CFGR_PLLXTPRE	            17
#define CFGR_USBPRE		            22


/***************************** RCC_CLOCK_TYPE *****************************/

#define RCC_HSI                     1
#define RCC_HSE                     2
#define RCC_PLL                     3


/***************************** RCC_PLL_TYPE *****************************/

#define RCC_PLL_HSI_BY_2            1
#define RCC_PLL_HSE_BY_2            2
#define RCC_PLL_HSE    		        3

/***************************** EN/DISABLE *******************************/

#define ENABLED						1
#define DISABLED		     		2

/***************************** RCC_HSE_BYPASS ***************************/

#define BYPASSED					1
#define NOT_BYPASSED				2

/************************** Masks For magic numbers *********************/

#define HSITRIM_MASK 				0x000000F8
#define PLLMUL_MASK 				0x003C0000
#define MCO_MASK					0x07000000
#define SW_MASK						0x00000003

#define AHB_PRESCALER_MASK			0x000000F0
#define APB1_PRESCALER_MASK			0x00000700
#define APB2_PRESCALER_MASK			0x00003800

/******************************* MCO_CLOCK ******************************/

#define MCO_NO_CLOCK                000
#define MCO_SYSCLK                  100
#define MCO_HSI_CLOCK               101
#define MCO_HSE_CLOCK               110
#define MCO_PLL_CLOCK_BY_2          111

/******************************* RCC_SYSCLK ******************************/

#define SYSCLK_HSI                  00
#define SYSCLK_HSE                  01
#define SYSCLK_PLL                  10


/*******************************   PPRE1    ******************************/

#define PPRE1_NO_CLOCK             000
#define PPRE1_BY_2                 100
#define PPRE1_BY_4                 101
#define PPRE1_BY_8                 110
#define PPRE1_BY_16                111

/*******************************   PPRE2    ******************************/

#define PPRE2_NO_CLOCK             000
#define PPRE2_BY_2                 100
#define PPRE2_BY_4                 101
#define PPRE2_BY_8                 110
#define PPRE2_BY_16                111

/*******************************    AHB     ******************************/

#define AHB_NO_CLOCK               0000
#define AHB_BY_2                   1000
#define AHB_BY_4                   1001
#define AHB_BY_8                   1010
#define AHB_BY_16                  1011
#define AHB_BY_64                  1100
#define AHB_BY_128                 1101
#define AHB_BY_256                 1110
#define AHB_BY_512                 1111

#endif /* RCC_RCC_PVT_H_ */
