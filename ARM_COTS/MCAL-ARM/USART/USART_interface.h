/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : USART  				******************/
/*************	 Date    : 31 Oct. 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_


void USART_vInit(void);


/**************************************** Sync. ****************************************/

void USART_vTransmitChar_Sync(u8 Copy_u8Data);

void USART_vTransmitString_Sync(u8* Copy_pu8Data);

u8   USART_u8ReceiveChar_Sync(void);

void USART_vReceiveString_Sync(u8* Copy_pu8Data/* return data */);

/**************************************** Async. ****************************************/

void USART_vTransmitChar_Async(u8 Copy_u8Data);

u8   USART_u8ReceiveChar_Async(void);

void USART_vTransmitString_Async(u8* Copy_pu8Data);

u8 USART_vReceiveString_Async(void);

void USART_vSetCallBack(void (* Pf_vUSART_CallBack)(void));

#endif /* MCAL_USART_USART_INTERFACE_H_ */
