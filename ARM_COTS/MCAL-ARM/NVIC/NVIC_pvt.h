/*
 * NVIC_pvt.h
 *
 *  Created on: Nov 3, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_NVIC_NVIC_PVT_H_
#define MCAL_ARM_NVIC_NVIC_PVT_H_


#define NVIC_BASE			0xE000E100UL
#define NVIC_ISER0			*((volatile u32*) (NVIC_BASE + 0x000)) //enable external interrupt from 0 to 31
#define NVIC_ISER1			*((volatile u32 *)(NVIC_BASE + 0x004)) //enable external interrupt from 32 to 63
#define NVIC_ISER2			*((volatile u32 *)(NVIC_BASE + 0x008)) //enable external interrupt from 64 to 80
#define NVIC_ICER0			*((volatile u32 *)(NVIC_BASE + 0x080)) //disable external interrupt from 0 to 31
#define NVIC_ICER1			*((volatile u32 *)(NVIC_BASE + 0x084)) //disable external interrupt from 32 to 63
#define NVIC_ICER2			*((volatile u32 *)(NVIC_BASE + 0x088)) //disable external interrupt from 64 to 80

#define NVIC_ISPR0			*((volatile u32 *)(NVIC_BASE + 0x100))
#define NVIC_ISPR1			*((volatile u32 *)(NVIC_BASE + 0x104))
#define NVIC_ISPR2			*((volatile u32 *)(NVIC_BASE + 0x108))
#define NVIC_ICPR0			*((volatile u32 *)(NVIC_BASE + 0x100))
#define NVIC_ICPR1			*((volatile u32 *)(NVIC_BASE + 0x184))
#define NVIC_ICPR2			*((volatile u32 *)(NVIC_BASE + 0x188))

#define NVIC_IABR0			*((volatile u32 *)(NVIC_BASE + 0x200))
#define NVIC_IABR1			*((volatile u32 *)(NVIC_BASE + 0x204))
#define NVIC_IABR2			*((volatile u32 *)(NVIC_BASE + 0x208))

#define NVIC_IPR			((volatile u8 *)(NVIC_BASE + 0x300))
//#define NVIC_IPR20			*((volatile u32 *)(NVIC_BASE + 0x320))
#define SCB_AIRCR			*((volatile u32*)(0xE000ED00 + 0x0C))

#define NVIC_STIR			*((volatile u32 *)(NVIC_BASE + 0xE00))

#define NVIC_GROUP_SUB		0x05FA0300

#endif /* MCAL_ARM_NVIC_NVIC_PVT_H_ */
