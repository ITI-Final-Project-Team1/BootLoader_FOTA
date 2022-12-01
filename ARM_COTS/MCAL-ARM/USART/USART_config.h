/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : USART  				******************/
/*************	 Date    : 31 Oct. 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/


#ifndef MCAL_USART_USART_CONFIG_H_
#define MCAL_USART_USART_CONFIG_H_

#define F_CPU								8000000UL
#define USART1_BAUD_RATE					9600

#define USART1_INTERRUPT_ENABLE				ENABLED


#define USART1_PARITY						DISABLED

#if USART1_PARITY == ENABLED
	#define USART1_PARITY_TYPE				EVEN_PARITY
#endif

#define USART1_STOP_BITS_NO					ONE_STOP_BIT



#endif /* MCAL_USART_USART_CONFIG_H_ */
