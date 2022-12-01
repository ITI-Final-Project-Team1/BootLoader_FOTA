/*
 * EXTI_int.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_EXTI_EXTI_INT_H_
#define MCAL_ARM_EXTI_EXTI_INT_H_

#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif


#include "../GPIO/GPIO_int.h"
#include "EXTI_pvt.h"


/*
 *=======================================================================
 *						User type definitions (structures)
 *=======================================================================
 *
*/
typedef struct
{
	u8 					EXTI_InputLineNumber ;
	GPIOxHandle_t		GPIO_Port;
	u16 				GPIO_PIN ;
	u8					IVT_IRQ_Number ;

}EXTI_GPIO_MAPPING_t;

typedef struct
{
	EXTI_GPIO_MAPPING_t 		EXTI_PIN ;	//Specifies the External interrupt GPIO mapping,
									 	 		//This Parameter must be set based on @ref EXTI_define

	u8 				Trigger_Case ;			//Specifies RISING or Falling or Both Trigger.
												//This parameter must be set based @ref EXTI_Trigger_define

	u8 				IRQ_EN ;				//Enable or Disable the EXTI IRQ (That will enable the IRQ MASK in EXTI
												//And also in the NVIC Interrupt Controller).
												//This parameter must be set based @ref EXTI_IRQ_define

	void (* Ptr_IRQ_CallBack)(void);			//Set the C Function() which will be called once the IRQ Happen

}EXTI_PinConfig_t;

typedef EXTI_PinConfig_t *  EXTI_PinCFGHandle;
//=======================================================================


//---------------------------------------------------------
//Macros Configuration References
//---------------------------------------------------------

//@ref EXTI_define
//EXTI0
#define EXTI0PA0		(EXTI_GPIO_MAPPING_t){EXTI0, GPIOA, GPIO_PIN_0, EXTI_NVIC_EXTI0_IRQ}
#define EXTI0PB0		(EXTI_GPIO_MAPPING_t){EXTI0, GPIOB, GPIO_PIN_0, EXTI_NVIC_EXTI0_IRQ}
#define EXTI0PC0		(EXTI_GPIO_MAPPING_t){EXTI0, GPIOC, GPIO_PIN_0, EXTI_NVIC_EXTI0_IRQ}
#define EXTI0PD0		(EXTI_GPIO_MAPPING_t){EXTI0, GPIOD, GPIO_PIN_0, EXTI_NVIC_EXTI0_IRQ}

//EXTI1
#define EXTI1PA1		(EXTI_GPIO_MAPPING_t){EXTI1, GPIOA, GPIO_PIN_1, EXTI_NVIC_EXTI1_IRQ}
#define EXTI1PB1		(EXTI_GPIO_MAPPING_t){EXTI1, GPIOB, GPIO_PIN_1, EXTI_NVIC_EXTI1_IRQ}
#define EXTI1PC1		(EXTI_GPIO_MAPPING_t){EXTI1, GPIOC, GPIO_PIN_1, EXTI_NVIC_EXTI1_IRQ}
#define EXTI1PD1		(EXTI_GPIO_MAPPING_t){EXTI1, GPIOD, GPIO_PIN_1, EXTI_NVIC_EXTI1_IRQ}

//EXTI2
#define EXTI2PA2		(EXTI_GPIO_MAPPING_t){EXTI2, GPIOA, GPIO_PIN_2, EXTI_NVIC_EXTI2_IRQ}
#define EXTI2PB2		(EXTI_GPIO_MAPPING_t){EXTI2, GPIOB, GPIO_PIN_2, EXTI_NVIC_EXTI2_IRQ}
#define EXTI2PC2		(EXTI_GPIO_MAPPING_t){EXTI2, GPIOC, GPIO_PIN_2, EXTI_NVIC_EXTI2_IRQ}
#define EXTI2PD2		(EXTI_GPIO_MAPPING_t){EXTI2, GPIOD, GPIO_PIN_2, EXTI_NVIC_EXTI2_IRQ}

//EXTI3
#define EXTI3PA3		(EXTI_GPIO_MAPPING_t){EXTI3, GPIOA, GPIO_PIN_3, EXTI_NVIC_EXTI3_IRQ}
#define EXTI3PB3		(EXTI_GPIO_MAPPING_t){EXTI3, GPIOB, GPIO_PIN_3, EXTI_NVIC_EXTI3_IRQ}
#define EXTI3PC3		(EXTI_GPIO_MAPPING_t){EXTI3, GPIOC, GPIO_PIN_3, EXTI_NVIC_EXTI3_IRQ}
#define EXTI3PD3		(EXTI_GPIO_MAPPING_t){EXTI3, GPIOD, GPIO_PIN_3, EXTI_NVIC_EXTI3_IRQ}

//EXTI4
#define EXTI4PA4		(EXTI_GPIO_MAPPING_t){EXTI4, GPIOA, GPIO_PIN_4, EXTI_NVIC_EXTI4_IRQ}
#define EXTI4PB4		(EXTI_GPIO_MAPPING_t){EXTI4, GPIOB, GPIO_PIN_4, EXTI_NVIC_EXTI4_IRQ}
#define EXTI4PC4		(EXTI_GPIO_MAPPING_t){EXTI4, GPIOC, GPIO_PIN_4, EXTI_NVIC_EXTI4_IRQ}
#define EXTI4PD4		(EXTI_GPIO_MAPPING_t){EXTI4, GPIOD, GPIO_PIN_4, EXTI_NVIC_EXTI4_IRQ}

//EXTI5
#define EXTI5PA5		(EXTI_GPIO_MAPPING_t){EXTI5, GPIOA, GPIO_PIN_5, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI5PB5		(EXTI_GPIO_MAPPING_t){EXTI5, GPIOB, GPIO_PIN_5, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI5PC5		(EXTI_GPIO_MAPPING_t){EXTI5, GPIOC, GPIO_PIN_5, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI5PD5		(EXTI_GPIO_MAPPING_t){EXTI5, GPIOD, GPIO_PIN_5, EXTI_NVIC_EXTI5_9_IRQ}

//EXTI6
#define EXTI6PA6		(EXTI_GPIO_MAPPING_t){EXTI6, GPIOA, GPIO_PIN_6, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI6PB6		(EXTI_GPIO_MAPPING_t){EXTI6, GPIOB, GPIO_PIN_6, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI6PC6		(EXTI_GPIO_MAPPING_t){EXTI6, GPIOC, GPIO_PIN_6, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI6PD6		(EXTI_GPIO_MAPPING_t){EXTI6, GPIOD, GPIO_PIN_6, EXTI_NVIC_EXTI5_9_IRQ}

//EXTI7
#define EXTI7PA7		(EXTI_GPIO_MAPPING_t){EXTI7, GPIOA, GPIO_PIN_7, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI7PB7		(EXTI_GPIO_MAPPING_t){EXTI7, GPIOB, GPIO_PIN_7, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI7PC7		(EXTI_GPIO_MAPPING_t){EXTI7, GPIOC, GPIO_PIN_7, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI7PD7		(EXTI_GPIO_MAPPING_t){EXTI7, GPIOD, GPIO_PIN_7, EXTI_NVIC_EXTI5_9_IRQ}

//EXTI8
#define EXTI8PA8		(EXTI_GPIO_MAPPING_t){EXTI8, GPIOA, GPIO_PIN_8, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI8PB8		(EXTI_GPIO_MAPPING_t){EXTI8, GPIOB, GPIO_PIN_8, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI8PC8		(EXTI_GPIO_MAPPING_t){EXTI8, GPIOC, GPIO_PIN_8, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI8PD8		(EXTI_GPIO_MAPPING_t){EXTI8, GPIOD, GPIO_PIN_8, EXTI_NVIC_EXTI5_9_IRQ}

//EXTI9
#define EXTI9PA9		(EXTI_GPIO_MAPPING_t){EXTI9, GPIOA, GPIO_PIN_9, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI9PB9		(EXTI_GPIO_MAPPING_t){EXTI9, GPIOB, GPIO_PIN_9, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI9PC9		(EXTI_GPIO_MAPPING_t){EXTI9, GPIOC, GPIO_PIN_9, EXTI_NVIC_EXTI5_9_IRQ}
#define EXTI9PD9		(EXTI_GPIO_MAPPING_t){EXTI9, GPIOD, GPIO_PIN_9, EXTI_NVIC_EXTI5_9_IRQ}

//EXTI10
#define EXTI10PA10		(EXTI_GPIO_MAPPING_t){EXTI10, GPIOA, GPIO_PIN_10, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI10PB10		(EXTI_GPIO_MAPPING_t){EXTI10, GPIOB, GPIO_PIN_10, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI10PC10		(EXTI_GPIO_MAPPING_t){EXTI10, GPIOC, GPIO_PIN_10, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI10PD10		(EXTI_GPIO_MAPPING_t){EXTI10, GPIOD, GPIO_PIN_10, EXTI_NVIC_EXTI10_15_IRQ}

//EXTI11
#define EXTI11PA11		(EXTI_GPIO_MAPPING_t){EXTI11, GPIOA, GPIO_PIN_11, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI11PB11		(EXTI_GPIO_MAPPING_t){EXTI11, GPIOB, GPIO_PIN_11, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI11PC11		(EXTI_GPIO_MAPPING_t){EXTI11, GPIOC, GPIO_PIN_11, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI11PD11		(EXTI_GPIO_MAPPING_t){EXTI11, GPIOD, GPIO_PIN_11, EXTI_NVIC_EXTI10_15_IRQ}

//EXTI12
#define EXTI12PA12		(EXTI_GPIO_MAPPING_t){EXTI12, GPIOA, GPIO_PIN_12, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI12PB12		(EXTI_GPIO_MAPPING_t){EXTI12, GPIOB, GPIO_PIN_12, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI12PC12		(EXTI_GPIO_MAPPING_t){EXTI12, GPIOC, GPIO_PIN_12, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI12PD12		(EXTI_GPIO_MAPPING_t){EXTI12, GPIOD, GPIO_PIN_12, EXTI_NVIC_EXTI10_15_IRQ}

//EXTI13
#define EXTI13PA13		(EXTI_GPIO_MAPPING_t){EXTI13, GPIOA, GPIO_PIN_13, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI13PB13		(EXTI_GPIO_MAPPING_t){EXTI13, GPIOB, GPIO_PIN_13, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI13PC13		(EXTI_GPIO_MAPPING_t){EXTI13, GPIOC, GPIO_PIN_13, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI13PD13		(EXTI_GPIO_MAPPING_t){EXTI13, GPIOD, GPIO_PIN_13, EXTI_NVIC_EXTI10_15_IRQ}

//EXTI14
#define EXTI14PA14		(EXTI_GPIO_MAPPING_t){EXTI14, GPIOA, GPIO_PIN_14, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI14PB14		(EXTI_GPIO_MAPPING_t){EXTI14, GPIOB, GPIO_PIN_14, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI14PC14		(EXTI_GPIO_MAPPING_t){EXTI14, GPIOC, GPIO_PIN_14, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI14PD14		(EXTI_GPIO_MAPPING_t){EXTI14, GPIOD, GPIO_PIN_14, EXTI_NVIC_EXTI10_15_IRQ}

//EXTI15
#define EXTI15PA15		(EXTI_GPIO_MAPPING_t){EXTI15, GPIOA, GPIO_PIN_15, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI15PB15		(EXTI_GPIO_MAPPING_t){EXTI15, GPIOB, GPIO_PIN_15, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI15PC15		(EXTI_GPIO_MAPPING_t){EXTI15, GPIOC, GPIO_PIN_15, EXTI_NVIC_EXTI10_15_IRQ}
#define EXTI15PD15		(EXTI_GPIO_MAPPING_t){EXTI15, GPIOD, GPIO_PIN_15, EXTI_NVIC_EXTI10_15_IRQ}
//============================

//@ref EXTI_Trigger_define
#define EXTI_Trigger_RISING						0
#define EXTI_Trigger_FALLING					1
#define EXTI_Trigger_RisingAndFalling			2
//============================

//@ref EXTI_IRQ_define
#define EXTI_IRQ_Enable							1
#define EXTI_IRQ_Disable						0
//============================

//@ref Line Number
typedef enum
{
	EXTI_LINE0 = 0 ,
	EXTI_LINE1     ,
	EXTI_LINE2 	   ,
	EXTI_LINE3
}EXTI_LineNum_t;
//---------------------------------------------------------


/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

/**================================================================
 * @Fn 				-	MCAL_EXTI_GPIO_Init
 * @brief 			-	Initializes GPIO pin to be used with EXTI according to the specified parameters in pinConfig
 * @param [in] 		- 	EXTI_Config : includes pin configuration for EXTI
 * 									  set by @ref EXTI_DEFINE , @ref EXTI_TRIGGER_DEFINE and @ref EXTI_IRQ_DEFINE
 * @retval 			-	none
 * Note 			-	STM32f10xx MCU has GPIO A,B,B,D,E modules
 *                      but LQFP48 Package has only A,B, Part of C,D
 *                      Also mandatory to enable RCC clock for AFIO and the corresponding GPIO
 */
void MCAL_EXTI_vInit(EXTI_PinCFGHandle EXTI_cfg);

/**================================================================
 * @Fn 				-	MCAL_EXTI_GPIO_DeInit
 * @brief 			-	Reset EXTI registers to their initial values and NVIC corresponding IRQ mask
 * @retval 			-	none
 * Note 			-	none
 */
void MCAL_EXTI_vDeInit_AllGPIO (void);

/**================================================================
 * @Fn 				-	MCAL_EXTI_vUpdate
 * @brief 			-	Update GPIO pin to be used with EXTI according to the specified parameters in pinConfig
 * @param [in] 		- 	EXTI_Config :includes pin configuration for EXTI
 * 									 set by @ref EXTI_DEFINE , @ref EXTI_TRIGGER_DEFINE and @ref EXTI_IRQ_DEFINE
 * @retval 			-	none
 * Note 			-	none
 */
void MCAL_EXTI_vUpdate(EXTI_PinCFGHandle EXTI_cfg);

/**================================================================
 * @Fn 				-	MCAL_EXTI_vTriggerSwInterrupt
 * @brief 			-	to Trigger Software Interrupt
 * @param [in] 		- 	A_xLineId : set by @ref Line Number
 * @retval 			-	none
 * Note 			-	none
 */
void MCAL_EXTI_vTriggerSwInterrupt(EXTI_LineNum_t A_xLineId);



#ifdef __cplusplus
}
#endif

#endif /* MCAL_ARM_EXTI_EXTI_INT_H_ */
