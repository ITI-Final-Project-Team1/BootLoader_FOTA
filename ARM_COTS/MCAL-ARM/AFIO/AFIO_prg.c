/*
 * AFIO_prg.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Magdy Adel
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../GPIO/GPIO_int.h"
#include "AFIO_int.h"
#include "AFIO_pvt.h"
#include "AFIO_cfg.h"


#define AFIO_GPIO_EXTI_Mapping(x)			( (x==GPIOA)?0:\
											  (x==GPIOB)?1:\
											  (x==GPIOC)?2:\
											  (x==GPIOD)?3:\
											  (x==GPIOE)?4:0 )


void MCAL_AFIO_vSetEXTIConfig(GPIOxHandle_t GPIOx ,u8 A_u8LineNumber )
{
	u8 AFIO_EXTICR_Index = A_u8LineNumber / 4;
	u8 AFIO_EXTICR_Position = (A_u8LineNumber % 4) * 4 ;

	//clear four bit AFIO_GPIO_EXTI_Mapping(GPIOx)
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~( 0xf << AFIO_EXTICR_Position);
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ( ( AFIO_GPIO_EXTI_Mapping(GPIOx) & 0xf) << AFIO_EXTICR_Position);

}
