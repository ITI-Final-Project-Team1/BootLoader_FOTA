/*
 * TIMERS_int.h
 *
 *  Created on: Nov 17, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_TIMERS_TIMERS_INT_H_
#define MCAL_ARM_TIMERS_TIMERS_INT_H_


#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif


//=================================================================
//User type definitions (structures)
//=================================================================
//@brief  TIM Time Base Init structure definition
typedef struct
{
	u16 Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

	u16 CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

	u16 Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */

	u16 ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */
}TIMERx_Cfg_t;



// @brief  TIM Output Compare Init structure definition
typedef struct
{
	u16 TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

	u16 TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */

	u16 TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                   This parameter can be a number between 0x0000 and 0xFFFF */

	u16 TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

} TIM_OCInitTypeDef;
//=================================================================


//=================================================================
//Macros Configuration References
//=================================================================
//@ref TIMERx_define
typedef enum
{
	TIMER1 = 0	,
	TIMER2		,
	TIMER3     	,
	TIMER4 	   	,
	TIMER5
}TIMERx_t;

// @ref TIM_Counter_Mode
#define TIM_CounterMode_Up                 ((u16)0x0000)
#define TIM_CounterMode_Down               ((u16)0x0010)
#define TIM_CounterMode_CenterAligned1     ((u16)0x0020)
#define TIM_CounterMode_CenterAligned2     ((u16)0x0040)
#define TIM_CounterMode_CenterAligned3     ((u16)0x0060)


// @ref TIM_Clock_Division_CKD
#define TIM_CKD_DIV1                       ((u16)0x0000)
#define TIM_CKD_DIV2                       ((u16)0x0100)
#define TIM_CKD_DIV4                       ((u16)0x0200)


// @defgroup TIM_Channel
#define TIM_Channel_1                      ((u16)0x0000)
#define TIM_Channel_2                      ((u16)0x0004)
#define TIM_Channel_3                      ((u16)0x0008)
#define TIM_Channel_4                      ((u16)0x000C)


// @ref TIM_Output_Compare_and_PWM_modes
#define TIM_OCMode_Timing                  ((u16)0x0000)
#define TIM_OCMode_Active                  ((u16)0x0010)
#define TIM_OCMode_Inactive                ((u16)0x0020)
#define TIM_OCMode_Toggle                  ((u16)0x0030)
#define TIM_OCMode_PWM1                    ((u16)0x0060)
#define TIM_OCMode_PWM2                    ((u16)0x0070)

// @ref TIM_Output_Compare_state
#define TIM_OutputState_Disable            ((u16)0x0000)
#define TIM_OutputState_Enable             ((u16)0x0001)

// @ref TIM_Output_Compare_Polarity
#define TIM_OCPolarity_High                ((u16)0x0000)
#define TIM_OCPolarity_Low                 ((u16)0x0002)


// @ref TIM_Output_Compare_Preload_State
#define TIM_OCPreload_Enable               ((u16)0x0008)
#define TIM_OCPreload_Disable              ((u16)0x0000)
//=================================================================


/*
* ============================================================================================
* 							APIs Supported by "MCAL TIMER DRIVER"
* ============================================================================================
*/
void MCAL_TIMERx_vInit(TIMERx_t timer, TIMERx_Cfg_t* timerCFG);
void MCAL_TIMERx_vDeInit(TIMERx_t timer);
void MCAL_TIMERx_vStart(TIMERx_t timer);
void MCAL_TIMERx_vStop(TIMERx_t timer);
void MCAL_TIMERx_OC1Init(TIMERx_t timer, TIM_OCInitTypeDef* TIM_OCInitStruct);
void MCAL_TIMERx_OC1PreloadConfig(TIMERx_t timer, u16 TIM_OCPreload);
void MCAL_TIMERx_SetCompare1(TIMERx_t timer, u16 CompareVAL1);

void dus(u32 us);
void dms(u32 ms);


#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif


#endif /* MCAL_ARM_TIMERS_TIMERS_INT_H_ */
