/*
 * GPIO_pvt.h
 *
 *  Created on: Nov 2, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_GPIO_GPIO_PVT_H_
#define MCAL_ARM_GPIO_GPIO_PVT_H_


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_TypeDef;
//GPIO

//A,B fully included in LQFP48 Package
#define GPIOA_Base 								0x40010800UL
#define GPIOB_Base 								0x40010C00UL

//C,D Partial included in LQFP48 Package
#define GPIOC_Base 								0x40011000UL
#define GPIOD_Base 								0x40011400UL

//E not included in LQFP48 Package
#define GPIOE_Base 								0x40011800UL

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA									((GPIO_TypeDef *)GPIOA_Base)
#define GPIOB									((GPIO_TypeDef *)GPIOB_Base)
#define GPIOC									((GPIO_TypeDef *)GPIOC_Base)
#define GPIOD									((GPIO_TypeDef *)GPIOD_Base)
#define GPIOE									((GPIO_TypeDef *)GPIOE_Base)
//-------------------------end-----------------------------

#define PIN_0						((u16)0x0001) /* PIN 0 selected	*/
#define PIN_1						((u16)0x0002) /* PIN 1 selected	*/
#define PIN_2						((u16)0x0004) /* PIN 2 selected	*/
#define PIN_3						((u16)0x0008) /* PIN 3 selected	*/
#define PIN_4						((u16)0x0010) /* PIN 4 selected	*/
#define PIN_5						((u16)0x0020) /* PIN 5 selected	*/
#define PIN_6						((u16)0x0040) /* PIN 6 selected	*/
#define PIN_7						((u16)0x0080) /* PIN 7 selected	*/
#define PIN_8						((u16)0x0100) /* PIN 8 selected	*/
#define PIN_9						((u16)0x0200) /* PIN 9 selected	*/
#define PIN_10						((u16)0x0400) /* PIN 10 selected	*/
#define PIN_11						((u16)0x0800) /* PIN 11 selected	*/
#define PIN_12						((u16)0x1000) /* PIN 12 selected	*/
#define PIN_13						((u16)0x2000) /* PIN 13 selected	*/
#define PIN_14						((u16)0x4000) /* PIN 14 selected	*/
#define PIN_15						((u16)0x8000) /* PIN 15 selected	*/
#define PIN_All					((u16)0xFFFF) /* All Pins selected	*/

#define PIN_MASK					0x0000FFFFu /* PIN Mask for assert test */


#define PORTA				GPIOA
#define PORTB				GPIOB
#define PORTC				GPIOC


#endif /* MCAL_ARM_GPIO_GPIO_PVT_H_ */
