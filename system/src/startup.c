/*
 *  startup.c
 *  Created on: NOV 23, 2022
 *  Author: Magdy Adel
 */

#include "STD_TYPES.h"
//#include "../../COTS_ARM/LIB/STD_TYPES.h"
//#include "../../COTS_ARM/MCAL-ARM/RCC/RCC_int.h"
#include "../inc/startup.h"


/*
* ===================================================================================
* 						Global Variables
* ===================================================================================
*/
//Booking 1024 Byte located by .bss through un intialized array of int 256 element (256*4=1024B)
//static unsigned long Stack_top[256];//uninitialized array to store in bss ,,
typedef void(* const pHandler)(void);
pHandler gp_fn_ISRVectors[] __attribute__((section(".vectors"))) =
{
	//(void (*)()) ((unsigned long)Stack_top + sizeof(Stack_top)), //SRAM_START+SRAM_SIZE= stack start || SRAM End // The initial stack pointer
	(pHandler) &_E_stack,// The initial stack pointer
    Reset_Handler,
    NMI_Handler,
    H_Fault_Handler,
    MM_Fault_Handler,
    Bus_Fault_Handler,
    Usage_Fault_Handler,
	0,                                        // Reserved
	0,                                        // Reserved
	0,                                        // Reserved
	0,                                        // Reserved
	SVC_Handler,                              // SVCall handler
	DebugMon_Handler	,
	0,                                        // Reserved
    PendSV_Handler		,
    SysTick_Handler	   ,
	// ----------------------------------------------------------------------
	// Chip Level - STM32F10x
	WWDG_IRQHandler					,
	PVD_IRQHandler					,
	TAMPER_IRQHandler				,
	RTC_IRQHandler					,
	FLASH_IRQHandler				,
	RCC_IRQHandler					,
	EXTI0_IRQHandler				,
	EXTI1_IRQHandler				,
	EXTI2_IRQHandler				,
	EXTI3_IRQHandler				,
	EXTI4_IRQHandler				,
	DMA1_Channel1_IRQHandler		,
	DMA1_Channel2_IRQHandler		,
	DMA1_Channel3_IRQHandler		,
	DMA1_Channel4_IRQHandler		,
	DMA1_Channel5_IRQHandler		,
	DMA1_Channel6_IRQHandler		,
	DMA1_Channel7_IRQHandler		,
	ADC1_2_IRQHandler				,
	USB_HP_CAN1_TX_IRQHandler		,
	USB_LP_CAN1_RX0_IRQHandler		,
	CAN1_RX1_IRQHandler			    ,
	AN1_SCE_IRQHandler				,
	EXTI9_5_IRQHandler				,
	TIM1_BRK_TIM9_IRQHandler		,
	TIM1_UP_TIM10_IRQHandler		,
	TIM1_TRG_COM_TIM11_IRQHandler	,
	TIM1_BRK_IRQHandler			    ,
	TIM1_UP_IRQHandler				,
	TIM1_TRG_COM_IRQHandler		    ,
	TIM1_CC_IRQHandler				,
	TIM2_IRQHandler				    ,
	TIM3_IRQHandler				    ,
	TIM4_IRQHandler				    ,
	I2C1_EV_IRQHandler				,
	I2C1_ER_IRQHandler				,
	I2C2_EV_IRQHandler				,
	I2C2_ER_IRQHandler				,
	SPI1_IRQHandler				    ,
	SPI2_IRQHandler				    ,
	USART1_IRQHandler				,
	USART2_IRQHandler				,
	USART3_IRQHandler				,
	EXTI15_10_IRQHandler			,
	RTCAlarm_IRQHandler			    ,
	USBWakeUp_IRQHandler				
};
/* ================================================================================== */


/*
* ===================================================================================
* 						Functions Implementations
* ===================================================================================
*/
void Default_Handler()
{
	Reset_Handler();
}

void Reset_Handler(void)
{
	
	/************ Setup the microcontroller system *****/
	//Enable HSI Clock
	//MCAL_RCC_vInit();
	/* Disable all interrupts and clear pending bits  */
	//MCAL_RCC_vDisableAllInterrupt();
	// SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
	/***************************************************/


	/************ Copy Data from FLASH to SRAM ********/
	u32 DATA_SIZE = (u8*)&_E_DATA - (u8*)&_S_DATA;
	u32 i=0,j=0;
	u8* P_src = (u8*)&_E_text;
	u8* P_dis = (u8*)&_S_DATA;
	for( i=0 ; i<DATA_SIZE ; i++)
	{
		*((u8*)P_dis++) = *((u8*)P_src++);
	}
	/***************************************************/


	/*********** initialize .bss with 0 ****************/
	u32 BSS_SIZE = (u8*)&_E_bss - (u8*)&_S_bss;
	P_dis = (u8*)&_S_bss;
	for( j=0 ; j<BSS_SIZE ; j++)
	{
		*((u8*)P_dis++) = (u8)0;
	}
	/***************************************************/
	
	
	/*********** Enable HSI Interrupt ******************/
	//MCAL_RCC_vEnHSIInterrupt();
	/***************************************************/
	
	
	/**************** Call main ************************/
	main();
	/***************************************************/
}
/* ================================================================================== */
