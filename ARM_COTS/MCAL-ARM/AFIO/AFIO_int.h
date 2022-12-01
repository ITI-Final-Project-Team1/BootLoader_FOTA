/*
 * AFIO_int.h
 *
 *  Created on: Nov 5, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_AFIO_AFIO_INT_H_
#define MCAL_ARM_AFIO_AFIO_INT_H_

#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif



void MCAL_AFIO_vSetEXTIConfig(GPIOxHandle_t GPIOx ,u8 A_u8LineNumber );



#ifdef __cplusplus
}
#endif

#endif /* MCAL_ARM_AFIO_AFIO_INT_H_ */
