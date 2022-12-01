/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : GPIO  				******************/
/*************	 Date    : 17 Oct. 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/

#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_


#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_config.h"
#include "../../MCAL/GPIO/GPIO_private.h"

/*
 * You can choose these options only for GPIO_CONFIG_TYPE:
 * - LINKTIME_CONFIG
 * - PREBUILD_CONFIG
 */



#if GPIO_CONFIG_TYPE == PREBUILD_CONFIG

	/*
	 * You can choose these options only
	 * for Copy_u8PortNo :
	 * - GPIO_PORTA
	 * - GPIO_PORTB
	 * - GPIO_PORTC
	 *
	 * for Copy_u8PinNo :
	 * - PIN0
	 * - PIN1
	 * - PIN2
	 * - PIN3
	 * - PIN4
	 * - PIN5
	 * - PIN6
	 * - PIN7
	 * - PIN8
	 * - PIN9
	 * - PIN10
	 * - PIN11
	 * - PIN12
	 * - PIN13
	 * - PIN14
	 * - PIN15
	 *
	 * for Copy_u8Dir :
	 * - OUTPUT_2MHZ_GP_PP
	 * - OUTPUT_2MHZ_GP_OD
	 * - OUTPUT_2MHZ_AF_PP
	 * - OUTPUT_2MHZ_AF_OD
	 *
	 * - OUTPUT_10MHZ_GP_PP
	 * - OUTPUT_10MHZ_GP_OD
	 * - OUTPUT_10MHZ_AF_PP
	 * - OUTPUT_10MHZ_AF_OD
	 *
	 * - OUTPUT_50MHZ_GP_PP
	 * - OUTPUT_50MHZ_GP_OD
	 * - OUTPUT_50MHZ_AF_PP
	 * - OUTPUT_50MHZ_AF_OD
	 *
	 * - INPUT_ANALOG
	 * - INPUT_FLOATING
	 * - INPUT_PULL_UP
	 * - INPUT_PULL_DOWN
	 *
	 *
	 *
	 * for Copy_u8Value :
	 * - HIGH
	 * - LOW
	 */
	void GPIO_vWritePinDirection(u8 Copy_u8PortNo, u8 Copy_u8PinNo, u8 Copy_u8Dir);
	void GPIO_vWritePinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo, u8 Copy_u8Value);
	void GPIO_vTogglePin(u8 Copy_u8PortNo, u8 Copy_u8PinNo);
	u8   GPIO_u8GetPinValue(u8 Copy_u8PortNo, u8 Copy_u8PinNo);

	void GPIO_vWritePortDirection_High(u8 Copy_u8PortNo, u32 Copy_u8Dir);
	void GPIO_vWritePortDirection_Low(u8 Copy_u8PortNo, u32 Copy_u8Dir);
	void GPIO_vWritePortValue_High(u8 Copy_u8PortNo, u8 Copy_u8Value);
	void GPIO_vWritePortValue_Low(u8 Copy_u8PortNo, u8 Copy_u8Value);

#elif GPIO_CONFIG_TYPE == LINKTIME_CONFIG

	typedef enum{
		GPIO_PORTA = 1,
		GPIO_PORTB,
		GPIO_PORTC,
	}GPIO_PORT_t;


	typedef enum{
		PIN0 = 0,
		PIN1,
		PIN2,
		PIN3,
		PIN4,
		PIN5,
		PIN6,
		PIN7,
		PIN8,
		PIN9,
		PIN10,
		PIN11,
		PIN12,
		PIN13,
		PIN14,
		PIN15,
	}GPIO_PIN_t;

	typedef enum{
		OUTPUT_2MHZ_GP_PP  = 0b0010,
		OUTPUT_2MHZ_GP_OD  = 0b0110,
		OUTPUT_2MHZ_AF_PP  = 0b1010,
		OUTPUT_2MHZ_AF_OD  = 0b1110,
		OUTPUT_10MHZ_GP_PP = 0b0001,
		OUTPUT_10MHZ_GP_OD = 0b0101,
		OUTPUT_10MHZ_AF_PP = 0b1001,
		OUTPUT_10MHZ_AF_OD = 0b1101,
		OUTPUT_50MHZ_GP_PP = 0b0011,
		OUTPUT_50MHZ_GP_OD = 0b0111,
		OUTPUT_50MHZ_AF_PP = 0b1011,
		OUTPUT_50MHZ_AF_OD = 0b1111,
		INPUT_ANALOG       = 0b0000,
		INPUT_FLOATING     = 0b0100,
		INPUT_PULL_UP      = 0b1000,
		INPUT_PULL_DOWN    = 0b1000,
	}GPIO_Direction_t;

	typedef struct
	{
		GPIO_PORT_t Port;
		GPIO_PIN_t Pin;
		GPIO_Direction_t Direction;
	}GPIO_Config_t;

	void GPIO_vInit(GPIO_Config_t* P_xGpio);
	void GPIO_vWritePinValue(GPIO_Config_t* P_xGpio, u8 Copy_u8Value);
	void GPIO_vTogglePin(GPIO_Config_t* P_xGpio);
	u8   GPIO_u8GetPinValue(GPIO_Config_t* P_xGpio);


	// CANCEL DIRECTION METHODS AND PUT IT IN GPIO_vInit

	void GPIO_vWritePortDirection_High(GPIO_Config_t* P_xGpio);
	void GPIO_vWritePortDirection_Low(GPIO_Config_t* P_xGpio);
	void GPIO_vWritePortValue_High(GPIO_Config_t* P_xGpio, u8 Copy_u8Value);
	void GPIO_vWritePortValue_Low(GPIO_Config_t* P_xGpio, u8 Copy_u8Value);

#endif


#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */
