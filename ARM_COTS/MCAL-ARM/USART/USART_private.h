/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : USART  				******************/
/*************	 Date    : 31 Oct. 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/


#ifndef MCAL_USART_USART_PRIVATE_H_
#define MCAL_USART_USART_PRIVATE_H_

#include "../../LIB/STD_TYPES.h"

#define USART1_BASE_ADDRESS		0x40013800

typedef struct
{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;
}USART_MemoryMap_t;

#define USART1					((volatile USART_MemoryMap_t*)(USART1_BASE_ADDRESS))


/***************************** USART_SR bits *****************************/

#define SR_PE					0
#define SR_RXNE		            5
#define SR_TC					6
#define SR_TXE					7

/***************************** USART_CR1 bits *****************************/

#define CR1_RE		            2
#define CR1_TE		            3
#define CR1_RXNEIE		        5
#define CR1_TCIE				6
#define CR1_TXEIE		        7
#define CR1_PEIE		        8
#define CR1_PS			        9
#define CR1_PCE			        10
#define CR1_M			        12
#define CR1_UE					13


/***************************** USART_CR2 bits *****************************/

#define CR2_CLKEN	            11
#define CR2_STOP1	            12
#define CR2_STOP2		        13


/********************************* Enable *********************************/
#define DISABLED				0
#define ENABLED					1

/********************************* parity *********************************/
#define EVEN_PARITY				0
#define ODD_PARITY				1

/******************************** Stop Bits *******************************/
#define ONE_STOP_BIT			0
#define TWO_STOP_BIT			2

/******************************** threshold *******************************/
#define THRESHOLD_VALUE  		9000000UL
#define CARRIAGE_NUMBER	  		13

// TODO : still have 4 USARTs, I don't implement them yet.


#endif /* MCAL_USART_USART_PRIVATE_H_ */
