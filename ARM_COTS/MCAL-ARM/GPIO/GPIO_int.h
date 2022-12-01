/*
 * GPIO_int.h
 *
 *  Created on: Nov 2, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_GPIO_GPIO_INT_H_
#define MCAL_ARM_GPIO_GPIO_INT_H_

#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif



#include "GPIO_pvt.h"

//=================================================================
//Macros Configuration References
//=================================================================

//@ref GPIO_PORT_define
#define GPIO_PORTA			PORTA
#define GPIO_PORTB			PORTB
#define GPIO_PORTC			PORTC
//--------------------

//@ref GPIO_PINS_define
#define GPIO_PIN_0			PIN_0	 /* PIN 0 selected	*/
#define GPIO_PIN_1			PIN_1	 /* PIN 1 selected	*/
#define GPIO_PIN_2			PIN_2	 /* PIN 2 selected	*/
#define GPIO_PIN_3			PIN_3	 /* PIN 3 selected	*/
#define GPIO_PIN_4			PIN_4	 /* PIN 4 selected	*/
#define GPIO_PIN_5			PIN_5	 /* PIN 5 selected	*/
#define GPIO_PIN_6			PIN_6	 /* PIN 6 selected	*/
#define GPIO_PIN_7			PIN_7	 /* PIN 7 selected	*/
#define GPIO_PIN_8			PIN_8	 /* PIN 8 selected	*/
#define GPIO_PIN_9			PIN_9	 /* PIN 9 selected	*/
#define GPIO_PIN_10			PIN_10	 /* PIN 10 selected	*/
#define GPIO_PIN_11			PIN_11	 /* PIN 11 selected	*/
#define GPIO_PIN_12			PIN_12	 /* PIN 12 selected	*/
#define GPIO_PIN_13			PIN_13	 /* PIN 13 selected	*/
#define GPIO_PIN_14			PIN_14	 /* PIN 14 selected	*/
#define GPIO_PIN_15			PIN_15	 /* PIN 15 selected	*/
#define GPIO_PIN_All		PIN_Al /* All Pins selected	*/

#define GPIO_PIN_MASK		PIN_MAK /* PIN Mask for assert test */
//--------------------

//@ref GPIO_MODE_define
typedef enum
{ GPIO_MODE_Analog = 0       ,  //0: Analog mode
  GPIO_Mode_IN_Floating =1   ,  //1: Floating input (reset state)
  GPIO_Mode_IN_PullUp        ,  //2: Input with pull-up / pull-down
  GPIO_Mode_IN_PullDown      ,  //3: pull-down
  GPIO_Mode_OUT_PushPull     ,	//4: General purpose output push-pull
  GPIO_Mode_OUT_OpenDrain    ,	//5: General purpose output Open-drain
  GPIO_Mode_AF_OUT_PushPull  ,	//6: Alternate function output Push-pull
  GPIO_Mode_AF_OUT_OpenDrain ,	//7: Alternate function output Open-drain
  GPIO_MODE_AF_IN 				//8: Alternate function Input
}GPIOMode_t;
//--------------------

//@ref GPIO_SPEED_define
typedef enum
{
  GPIO_Speed_10M = 1,		//1: Output mode, max speed 10 MHz.
  GPIO_Speed_2M, 			//2: Output mode, max speed 2 MHz.
  GPIO_Speed_50M 			//3: Output mode, max speed 50 MHz.
}GPIOSpeed_t;
//--------------------

// @ref GPIO_PIN_state
typedef enum
{
	GPIO_PIN_LOW = 0 ,
	GPIO_PIN_HIGH
}GPIOPinStatus_t;
//--------------------

//@ref GPIO_RETURN_LOCK
typedef enum {
	GPIO_RETURN_LOCK_EN = 0,
	GPIO_RETURN_LOCK_ERROR
}GPIO_ErrorStatusType ;
//=================================================================


//=================================================================
//User type definitions (structures)
//=================================================================
typedef struct{
	u16 GPIO_PinNumber				;//Specifies the GPIO pins to be configure
											//this parameter must be set based on @ref GPIO_PINS_define
	GPIOMode_t GPIO_MODE			;//Specifies the operation mode for the selected pins
											//this parameter must be set based on @ref GPIO_MODE_define
	GPIOSpeed_t GPIO_OUTPUT_SPEED	;//Specifies the Speed for the selected pins
											//this parameter must be set based on @ref GPIO_SPEED_define
}GPIO_PinConfig_t;

typedef GPIO_PinConfig_t *  GPIOxPinHandle_t;
typedef GPIO_TypeDef *  GPIOxHandle_t;
//=================================================================


/*
* ============================================================================================
* 							APIs Supported by "MCAL GPIO DRIVER"
* ============================================================================================
*/

/**=======================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initializes GPIOx PINy according to the specified
 * 				 parameters in the PinConfig
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-PinConfig: pointer to a GPIO_PinConfig_t structure that
 * 				 contains the configuration information for the specified
 * 				  GPIO PIN.
 *
 * @retval		-None
 *
 * Note			-STM32F103C6 MCU has GPIO A,B,C,D and E Modules but LQFP4
 *              	 package has only GPIO A,B and part of C AND D exported as
 *                external PINs from the MCU.
 */
void MCAL_GPIO_vInit(GPIOxHandle_t GPIOx , GPIOxPinHandle_t PinConfig);

/**=======================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-Reset GPIOx PINy according to the specified
 * 				 parameters in the PinConfig
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @retval		-None
 *
 * Note			-None
 */
void MCAL_GPIO_vDeInit(GPIOxHandle_t GPIOx);

/**=======================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Read specific PIN
 * 				 parameters in the PinConfig
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 * @param[in] 	-PinNumber: Set PinNumber according GPIO_PINS_define
 *
 * @retval		-the input pin value (two values based on @ref GPIO_PIN_state)
 *
 * Note			-None
 */
GPIOPinStatus_t MCAL_GPIO_u8ReadPin(GPIOxHandle_t GPIOx , u16 PinNumber);

/**=======================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-Read the input PORT value
 * 				 parameters in the PinConfig
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 * @retval		-the input PORT value
 * Note			-None
 */
u16 MCAL_GPIO_u16ReadPort(GPIOxHandle_t GPIOx );

/**=======================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief 		-Write specific input PIN
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-PinNumber: Set PinNumber according GPIO_PINS_define
 * @param[in] 	-Value: Pin Value  (two values based on @ref GPIO_PIN_state)
 *
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_vWritePin(GPIOxHandle_t GPIOx , u16 PinNumber, GPIOPinStatus_t Value);

/**=======================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-Write on output PORT
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-Value: Pin Value
 *
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_vWritePort(GPIOxHandle_t GPIOx , u16 Value);

/**=======================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-Toggle the specified GPIO pin
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-PinNumber: Set PinNumber according GPIO_PINS_define
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_vTogglePin(GPIOxHandle_t GPIOx , u16 PinNumber);

/**=======================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-The locking mechanism allows the IO configuration
 * 				 to be frozen
 *
 * @param[in] 	-GPIOx: where can be(A..E depending on device used)
 * 				 to select the GPIO peripheral
 *
 * @param[in] 	-PinNumber: Set PinNumber according GPIO_PINS_define
 * @retval		-OK, if pinConfig is locked Or ERROR if pin not locked
 * 				 (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note			-None
 */
GPIO_ErrorStatusType  MCAL_GPIO_enuLockPin(GPIOxHandle_t GPIOx , u16 PinNumber);



#ifdef __cplusplus
}
#endif

#endif /* MCAL_ARM_GPIO_GPIO_INT_H_ */
