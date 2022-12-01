/*
 * NVIC_int.h
 *
 *  Created on: Nov 3, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_NVIC_NVIC_INT_H_
#define MCAL_ARM_NVIC_NVIC_INT_H_

#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//NVIC IRQ Macros: IVT (Interrupt vector table) ==> For param: A_u8IntID
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define NO_SUB_PRIORITY 0

/////////////////////////
#define NVIC_PEND_SV        -6
#define NVIC_SYSTICK        -5
////////////////////////////
#define NVIC_SVCALL        -4
/////////////////////////
#define NVIC_MEMORYMANAGE  -3
#define NVIC_BUSFAULT      -2
#define NVIC_USAGEFAULT    -1
/////////////////////////

//EXTI-Enable
#define NVIC_EXTI0_IRQ		6
#define NVIC_EXTI1_IRQ		7
#define NVIC_EXTI2_IRQ		8
#define NVIC_EXTI3_IRQ		9
#define NVIC_EXTI4_IRQ		10
#define NVIC_EXTI5_9_IRQ		23
#define NVIC_EXTI10_15_IRQ		40


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

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// ==> For param: A_u8Group
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_GROUP4_SUB0		0
#define NVIC_GROUP3_SUB1		1
#define NVIC_GROUP2_SUB2		2
#define NVIC_GROUP1_SUB3		3
#define NVIC_GROUP0_SUB4		4
//=========================================================


/*
* ===================================================================================
* 						APIs Supported by "MCAL NVIC DRIVER"
* ===================================================================================
*/
void MCAL_NVIC_vEnableInterrupt(u8 A_u8IntID);
void MCAL_NVIC_vDisableInterrupt(u8 A_u8IntID);

void MCAL_NVIC_vSetPendingFlag(u8 A_u8IntID);
void MCAL_NVIC_vClearPendingFlag(u8 A_u8IntID);

u8 MCAL_NVIC_u8GetActiveFlag(u8 A_u8IntID);

void MCAL_NVIC_vSetPriority(s8 A_s8IntID, u8 A_u8GroupPriority, u8 A_u8Group_SubPriority);



#ifdef __cplusplus
}
#endif

#endif /* MCAL_ARM_NVIC_NVIC_INT_H_ */
