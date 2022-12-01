/*
 * EXTI_pvt.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_EXTI_EXTI_PVT_H_
#define MCAL_ARM_EXTI_EXTI_PVT_H_



//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: EXTI - BUS APB2
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI
#define EXTI_Base 				0x40010400UL

typedef struct{
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;
}EXTI_TypeDef;



#define EXTI					((EXTI_TypeDef *)EXTI_Base)
//-----------------------------------------------------------------


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//NVIC IRQ Macros: IVT (Interrupt vector table) ==> For param: A_u8IntID
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//EXTI-Enable
#define EXTI_NVIC_EXTI0_IRQ		6
#define EXTI_NVIC_EXTI1_IRQ		7
#define EXTI_NVIC_EXTI2_IRQ		8
#define EXTI_NVIC_EXTI3_IRQ		9
#define EXTI_NVIC_EXTI4_IRQ		10
#define EXTI_NVIC_EXTI5_9_IRQ		23
#define EXTI_NVIC_EXTI10_15_IRQ		40


//USART-Enable
#define NVIC_USART1_IRQ		37
#define NVIC_USART2_IRQ		38
#define NVIC_USART3_IRQ		39

//SPI-Enable
#define NVIC_SPI1_IRQ		35
#define NVIC_SPI2_IRQ		36

//I2C-Enable
#define NVIC_I2C1_EV_IRQ	31
#define NVIC_I2C1_ER_IRQ	32
#define NVIC_I2C2_EV_IRQ	33
#define NVIC_I2C2_ER_IRQ	34
//---------------------------------------


//Input Line Number
#define EXTI0				0
#define EXTI1				1
#define EXTI2				2
#define EXTI3				3
#define EXTI4				4
#define EXTI5				5
#define EXTI6				6
#define EXTI7				7
#define EXTI8				8
#define EXTI9				9
#define EXTI10				10
#define EXTI11				11
#define EXTI12				12
#define EXTI13				13
#define EXTI14				14
#define EXTI15				15





#endif /* MCAL_ARM_EXTI_EXTI_PVT_H_ */
