/*
 * SERVO_int.h
 *
 *  Created on: Nov 17, 2022
 *      Author: Magdy Adel
 */

#ifndef HAL_SERVO_MOTOR_SERVO_INT_H_
#define HAL_SERVO_MOTOR_SERVO_INT_H_

#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif


#define MinPulse 		420
#define MaxPulse  		2000





void SERVO_vInit(void);
void SERVOM_vStart(u8 Copy_u8Angle);
void SERVOM_vStop(void);
void SERVOM_vMax(void);
void SERVOM_vtest(u16 Copy_u8Angle);


#ifdef __cplusplus
}
#endif

#endif /* HAL_SERVO_MOTOR_SERVO_INT_H_ */
