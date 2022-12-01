/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : GPIO  				******************/
/*************	 Date    : 17 Oct. 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/

#ifndef MCAL_GPIO_GPIO_PRIVATE_H_
#define MCAL_GPIO_GPIO_PRIVATE_H_

#include "../../MCAL/GPIO/GPIO_config.h"

#define GPIOA_BASE_ADDRESS			  0x40010800
#define GPIOB_BASE_ADDRESS			  0x40010C00
#define GPIOC_BASE_ADDRESS			  0x40011000

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_MemoryMap_t;


#define GPIOA						((volatile GPIO_MemoryMap_t*)(GPIOA_BASE_ADDRESS))
#define GPIOB						((volatile GPIO_MemoryMap_t*)(GPIOB_BASE_ADDRESS))
#define GPIOC						((volatile GPIO_MemoryMap_t*)(GPIOC_BASE_ADDRESS))


#define PORT_HIGH					0xFF
#define PORT_LOW					0x00


#define LINKTIME_CONFIG				1
#define PREBUILD_CONFIG				2

#define LOW 						0
#define HIGH						1


#if GPIO_CONFIG_TYPE == PREBUILD_CONFIG


#define GPIO_PORTA			      	1
#define GPIO_PORTB			      	2
#define GPIO_PORTC			      	3


#define PIN0                        0
#define PIN1                        1
#define PIN2                        2
#define PIN3                        3
#define PIN4                        4
#define PIN5                        5
#define PIN6                        6
#define PIN7                        7
#define PIN8                        8
#define PIN9                        9
#define PIN10                       10
#define PIN11                       11
#define PIN12                       12
#define PIN13                       13
#define PIN14                       14
#define PIN15                       15


#define OUTPUT_2MHZ_GP_PP		    0b0010
#define	OUTPUT_2MHZ_GP_OD		    0b0110
#define OUTPUT_2MHZ_AF_PP			0b1010
#define OUTPUT_2MHZ_AF_OD			0b1110

#define OUTPUT_10MHZ_GP_PP		    0b0001
#define OUTPUT_10MHZ_GP_OD		    0b0101
#define OUTPUT_10MHZ_AF_PP		    0b1001
#define OUTPUT_10MHZ_AF_OD		    0b1101

#define OUTPUT_50MHZ_GP_PP		    0b0011
#define OUTPUT_50MHZ_GP_OD		    0b0111
#define OUTPUT_50MHZ_AF_PP		    0b1011
#define OUTPUT_50MHZ_AF_OD		    0b1111

#define INPUT_ANALOG				0b0000
#define INPUT_FLOATING			    0b0100
#define INPUT_PULL_UP			    0b1000
#define INPUT_PULL_DOWN			    0b1000


#elif GPIO_CONFIG_TYPE == LINKTIME_CONFIG


#endif



#endif /* MCAL_GPIO_GPIO_PRIVATE_H_ */
