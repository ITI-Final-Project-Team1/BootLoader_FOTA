/*
 *  startup.h
 *  Created on: NOV 23, 2022
 *  Author: Magdy Adel
 */

#ifndef _STARTUP_H_
#define _STARTUP_H_


/*
 *=======================================================================
 *						extern Variables & Funcs
 *=======================================================================
 *
*/
extern int mainBTL(void);
/***Symbols  from LinkerScript . ***/ 
extern u32 _E_stack;
//Symbols for copying data from flash to sram
extern u32 _E_text;
extern u32 _S_DATA;
extern u32 _E_DATA;
extern u32 _S_bss;
extern u32 _E_bss;

/* ===================================================================== */



/*
* ===================================================================================
* 						Functions Proyotypes
* ===================================================================================
*/
void Reset_Handler();

//make prototypes of functions __weak to be overriden by user when handling interrupts
// and make it __alias to be redefinition it and store in memory with the same address of alias func till it be defined
void NMI_Handler					(void) __attribute__((weak, alias("Default_Handler")));
void H_Fault_Handler				(void) __attribute__((weak, alias("Default_Handler")));
void MM_Fault_Handler				(void) __attribute__((weak, alias("Default_Handler")));
void Bus_Fault_Handler				(void) __attribute__((weak, alias("Default_Handler")));
void Usage_Fault_Handler			(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler					(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler				(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler					(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler				(void) __attribute__((weak, alias("Default_Handler")));

// Chip Level - STM32F10x
void WWDG_IRQHandler				(void) __attribute__ ((weak, alias ("Default_Handler")));
void PVD_IRQHandler					(void)    __attribute__ ((weak, alias ("Default_Handler")));
void TAMPER_IRQHandler				(void) __attribute__ ((weak, alias ("Default_Handler")));
void RTC_IRQHandler					(void)    __attribute__ ((weak, alias ("Default_Handler")));
void FLASH_IRQHandler				(void)  __attribute__ ((weak, alias ("Default_Handler")));
void RCC_IRQHandler					(void)    __attribute__ ((weak, alias ("Default_Handler")));
void EXTI0_IRQHandler				(void)  __attribute__ ((weak, alias ("Default_Handler")));
void EXTI1_IRQHandler				(void)  __attribute__ ((weak, alias ("Default_Handler")));
void EXTI2_IRQHandler				(void)  __attribute__ ((weak, alias ("Default_Handler")));
void EXTI3_IRQHandler				(void)  __attribute__ ((weak, alias ("Default_Handler")));
void EXTI4_IRQHandler				(void)  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel2_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel3_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel4_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel5_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel6_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel7_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void ADC1_2_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void USB_HP_CAN1_TX_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void USB_LP_CAN1_RX0_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void CAN1_RX1_IRQHandler			(void)__attribute__ ((weak, alias ("Default_Handler")));
void AN1_SCE_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void EXTI9_5_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler	(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM1_BRK_IRQHandler			(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM1_UP_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM1_TRG_COM_IRQHandler		(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM2_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM3_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void TIM4_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void I2C1_EV_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void I2C1_ER_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void I2C2_EV_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void I2C2_ER_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void SPI1_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void SPI2_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void USART1_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void USART2_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void USART3_IRQHandler				(void)__attribute__ ((weak, alias ("Default_Handler")));
void EXTI15_10_IRQHandler			(void)__attribute__ ((weak, alias ("Default_Handler")));
void RTCAlarm_IRQHandler			(void)__attribute__ ((weak, alias ("Default_Handler")));
void USBWakeUp_IRQHandler			(void)__attribute__ ((weak, alias ("Default_Handler")));
/* ================================================================================== */

#endif /* _STARTUP_H_ */