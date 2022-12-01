/*
 * AFIO_pvt.h
 *
 *  Created on: Nov 5, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_AFIO_AFIO_PVT_H_
#define MCAL_ARM_AFIO_AFIO_PVT_H_


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: EXTI - BUS APB2
//-*-*-*-*-*-*-*-*-*-*-*
//AFIO
#define AFIO_Base 				0x40010000L

typedef struct{
	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR[4] ;
	u32 		  RESERVED0 ; //0x18
	volatile u32 MAPR2 ; //0x1C
}AFIO_TypeDef;

#define AFIO					((AFIO_TypeDef *)AFIO_Base)
//-----------------------------------------------------------------


#endif /* MCAL_ARM_AFIO_AFIO_PVT_H_ */
