/*
 * USART_pvt.h
 *
 *  Created on: Nov 13, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_USART_USART_PVT_H_
#define MCAL_ARM_USART_USART_PVT_H_


//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

//APB2-BUS
#define USART1_Base			0x40013800UL
//APB1-BUS
#define USART2_Base			0x40004400UL
#define USART3_Base			0x40004800UL

typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}USART_TypeDef;

#define USART1				((USART_TypeDef *)USART1_Base)
#define USART2				((USART_TypeDef *)USART2_Base)
#define USART3				((USART_TypeDef *)USART3_Base)


//BaudRate Calculation
//USARTDIV = fclk / (16 * BaudRate)
//USARTDIV_MUL100 = u32((100 * fclk) / (16 * BaudRate) == (25 * fclk) / (4 * BaudRate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV) * 100
//DIV_Mantissa = Integer Part (USARTDIV)
//DIV_Fraction = ( (USARTDIV_MUL100 - DIV_Mantissa_MUL100) * 16) /100

#define USARTDIV(_PCLK_, _BAUD_)						(u32) (_PCLK_ / (16 * _BAUD_))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)					(u32) (25 * _PCLK_ / (4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_, _BAUD_)					(u32) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)						(u32) (USARTDIV(_PCLK_, _BAUD_))
#define DIV_Fraction(_PCLK_, _BAUD_)					(u32) (( (USARTDIV_MUL100(_PCLK_, _BAUD_) - Mantissa_MUL100(_PCLK_, _BAUD_)) * 16) /100)
#define USART_BRR_Register(_PCLK_, _BAUD_)				((Mantissa(_PCLK_, _BAUD_)) << 4) | ( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )



#endif /* MCAL_ARM_USART_USART_PVT_H_ */
