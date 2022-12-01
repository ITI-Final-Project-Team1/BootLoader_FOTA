/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : RCC  				******************/
/*************	 Date    : 12 Oct. 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/

#ifndef RCC_RCC_INT_H_
#define RCC_RCC_INT_H_

#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif



/*
 *=======================================================================
 *						Clock Enable Reference:
 *=======================================================================
 *
*/
//BUS ID
typedef enum {
	AHB,
	APB1,
	APB2,
}Bus_ID_t;

typedef enum {
	HSI,
	HSE,
	PLL,
}System_Clock_t;

typedef enum
{
	/************************ AHB **************************/
	DMA1_AHB  = 0,
	DMA2_AHB  = 1,
	SRAM_AHB  = 2,
	FLITF_AHB = 4,
	CRC_AHB   = 6,
	FSMC_AHB  = 8,
	SDIO_AHB  = 10,
	/************************ APB1 **************************/
	TIM2_APB1  = 0,
	TIM3_APB1  = 1,
	TIM4_APB1  = 2,
	TIM5_APB1  = 3,
	TIM6_APB1  = 4,
	TIM7_APB1  = 1,
	TIM12_APB1  = 6,
	TIM13_APB1  = 7,
	TIM14_APB1  = 8,
	WWDG_APB1   = 11,
	SPI2_APB1   = 14,
	SPI3_APB1   = 15,
	USART2_APB1 = 17,
	USART3_APB1 = 18,
	USART4_APB1 = 19,
	USART5_APB1 = 20,
	I2C1_APB1_APB1   = 21,
	I2C2_APB1   = 22,
	USB_APB1    = 23,
	CAN_APB1    = 25,
	BKP_APB1    = 27,
	PWR_APB1    = 28,
	DAC_APB1    = 29,
	/************************ APB2 **************************/
	AFIO_APB2   = 0,
	IOPA_APB2   = 2,
	IOPB_APB2   = 3,
	IOPC_APB2   = 4,
	IOPD_APB2   = 5,
	IOPE_APB2   = 6,
	IOPF_APB2   = 7,
	IOPG_APB2   = 8,
	ADC1_APB2   = 9,
	ADC2_APB2   = 10,
	TIM1_APB2   = 11,
	SPI1_APB2   = 12,
	TIM8_APB2   = 13,
	USART1_APB2 = 14,
	ADC3_APB2   = 15,
	TIM9_APB2   = 19,
	TIM10_APB2  = 20,
	TIM11_APB2  = 21,
}Prepherial_EN_t;

//===================================================================================



/*
* ===================================================================================
* 						APIs Supported by "MCAL RCC DRIVER"
* ===================================================================================
*/

void RCC_vInit(void);

/*
 * for Copy_u8busId choose from the options of the Bus_ID_t.
 *
 * for Copy_u16prepherial choose from the options of the Prepherial_EN_t .
 */
void RCC_vEnableClock (Prepherial_EN_t Copy_prepherial , Bus_ID_t Copy_busId );
void RCC_vDisableClock(Prepherial_EN_t Copy_prepherial , Bus_ID_t Copy_busId );

/*
 * for Copy_systemClock choose from the options of the System_Clock_t.
 */
void RCC_vSetSysClock(System_Clock_t Copy_systemClock);

void RCC_vRESET(Prepherial_EN_t Copy_prepherial , Bus_ID_t Copy_busId );

void RCC_vDisableAllInterrupt(void);
void RCC_vEnHSIInterrupt(void);

//===================================================================================



#ifdef __cplusplus
}
#endif

#endif /* RCC_RCC_INT_H_ */
