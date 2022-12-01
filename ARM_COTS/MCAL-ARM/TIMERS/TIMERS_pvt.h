/*
 * TIMERS_pvt.h
 *
 *  Created on: Nov 17, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_TIMERS_TIMERS_PVT_H_
#define MCAL_ARM_TIMERS_TIMERS_PVT_H_

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: TIMER - BUS
//-*-*-*-*-*-*-*-*-*-*-*
//TIM1 - APB2
#define TIM1_Base 				0x40012C00UL
//APB1
//TIM2
#define TIM2_Base 				0x40000000UL
//TIM3
#define TIM3_Base 				0x40000400UL
//TIM4
#define TIM4_Base 				0x40000800UL
//TIM5
#define TIM5_Base 				0x40000C00UL

typedef struct{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RESERVED0;
	volatile u32 CCRn[4];
	volatile u32 RESERVED1;
	volatile u32 DCR;
	volatile u32 DMAR;
}TIMx_TypeDef;


#define TIM1					((TIMx_TypeDef *)TIM1_Base)
#define TIM2					((TIMx_TypeDef *)TIM2_Base)
#define TIM3					((TIMx_TypeDef *)TIM3_Base)
#define TIM4					((TIMx_TypeDef *)TIM4_Base)
#define TIM5					((TIMx_TypeDef *)TIM5_Base)
//-----------------------------------------------------------------


/*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN                         ((u16)0x0001)            /*!< Counter enable */
#define  TIM_CR1_UDIS                        ((u16)0x0002)            /*!< Update disable */
#define  TIM_CR1_URS                         ((u16)0x0004)            /*!< Update request source */
#define  TIM_CR1_OPM                         ((u16)0x0008)            /*!< One pulse mode */
#define  TIM_CR1_DIR                         ((u16)0x0010)            /*!< Direction */

#define  TIM_CR1_CMS                         ((u16)0x0060)            /*!< CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0                       ((u16)0x0020)            /*!< Bit 0 */
#define  TIM_CR1_CMS_1                       ((u16)0x0040)            /*!< Bit 1 */

#define  TIM_CR1_ARPE                        ((u16)0x0080)            /*!< Auto-reload preload enable */

#define  TIM_CR1_CKD                         ((u16)0x0300)            /*!< CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0                       ((u16)0x0100)            /*!< Bit 0 */
#define  TIM_CR1_CKD_1                       ((u16)0x0200)            /*!< Bit 1 */


/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E                       ((u16)0x0001)            /*!< Capture/Compare 1 output enable */
#define  TIM_CCER_CC1P                       ((u16)0x0002)            /*!< Capture/Compare 1 output Polarity */
#define  TIM_CCER_CC1NE                      ((u16)0x0004)            /*!< Capture/Compare 1 Complementary output enable */
#define  TIM_CCER_CC1NP                      ((u16)0x0008)            /*!< Capture/Compare 1 Complementary output Polarity */
#define  TIM_CCER_CC2E                       ((u16)0x0010)            /*!< Capture/Compare 2 output enable */
#define  TIM_CCER_CC2P                       ((u16)0x0020)            /*!< Capture/Compare 2 output Polarity */
#define  TIM_CCER_CC2NE                      ((u16)0x0040)            /*!< Capture/Compare 2 Complementary output enable */
#define  TIM_CCER_CC2NP                      ((u16)0x0080)            /*!< Capture/Compare 2 Complementary output Polarity */
#define  TIM_CCER_CC3E                       ((u16)0x0100)            /*!< Capture/Compare 3 output enable */
#define  TIM_CCER_CC3P                       ((u16)0x0200)            /*!< Capture/Compare 3 output Polarity */
#define  TIM_CCER_CC3NE                      ((u16)0x0400)            /*!< Capture/Compare 3 Complementary output enable */
#define  TIM_CCER_CC3NP                      ((u16)0x0800)            /*!< Capture/Compare 3 Complementary output Polarity */
#define  TIM_CCER_CC4E                       ((u16)0x1000)            /*!< Capture/Compare 4 output enable */
#define  TIM_CCER_CC4P                       ((u16)0x2000)            /*!< Capture/Compare 4 output Polarity */
#define  TIM_CCER_CC4NP                      ((u16)0x8000)            /*!< Capture/Compare 4 Complementary output Polarity */



// @defgroup TIM_interrupt_sources
#define TIM_IT_Update                      ((u16)0x0001)
#define TIM_IT_CC1                         ((u16)0x0002)
#define TIM_IT_CC2                         ((u16)0x0004)
#define TIM_IT_CC3                         ((u16)0x0008)
#define TIM_IT_CC4                         ((u16)0x0010)
#define TIM_IT_COM                         ((u16)0x0020)
#define TIM_IT_Trigger                     ((u16)0x0040)
#define TIM_IT_Break                       ((u16)0x0080)

#endif /* MCAL_ARM_TIMERS_TIMERS_PVT_H_ */
