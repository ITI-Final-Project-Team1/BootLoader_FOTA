/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL-ARM/RCC/RCC_int.h"
#include "../../MCAL-ARM/USART/USART_int.h"
#include "../../MCAL-ARM/STK/STK_int.h"
#include "ESP8266_INTERFACE.h"




//================================================
void TransmitString_Sync(u8* Copy_pu8Data)
{
	u32 Local_u32Index=0;
	while(Copy_pu8Data[Local_u32Index] != '\0')
	{
		MCAL_USART_SendData(UART1, enable, (u16 *) &Copy_pu8Data[Local_u32Index] );
		//USART_vTransmitChar_Sync(Copy_pu8Data[Local_u32Index]);
		Local_u32Index++;
	}
}

void ReceiveString_Async(volatile u8* Copy_pu8Data/* return data */)
{
	u8 Localu8received = 0;
	u16 Local_u16Index = 0;
	MCAL_USART_ReceiveData(UART1,enable , (u16*)&Localu8received);

	while(Localu8received != 13) // Receiving process doesn't finished, so receive more
	{
		Copy_pu8Data[Local_u16Index] = Localu8received;
		Local_u16Index++;
	}
	Copy_pu8Data[Local_u16Index] = '\0';
}
//================================================


void MUSART_CallBack ( void );
u8 volatile Iterator = 0;
u8 volatile DataCome[200];
u8 volatile result =0;
u8 volatile RecievedData[60] ;

void MUSART_CallBack ( void ){
	//result =0;
	/* Receive ESP8266 Response */
	ReceiveString_Async(&DataCome[Iterator]);
	/* ------------------ */
	Iterator++;
	USART1_vClearFlags();

}



void USARTx_vInit(void)
{
	RCC_vEnableClock( IOPA_APB2 , APB2   );	/* Enable GPIOA */

	static USART_Config_t USART_ESP = {
		.USART_MODE =USART_MODE_TX_RX ,
		.BaudRate = USART_BaudRate_9600 ,
		.IRQ_Enable = USART_IRQ_Enable_RXNEIE ,
		.StopBits = USART_StopBits__1 ,
		.Payload_Length = USART_Payload_Length_8B,
		.P_IRQ_CallBack = MUSART_CallBack ,
	};
	MCAL_USART_Init(UART1 ,&USART_ESP);
	MCAL_USART_GPIO_Set_Pins(UART1);
}


void ValidateCommand( void )
{
	while(result ==0){
		for(u8 i=0;i<Iterator;i++)
		{
			if (DataCome[i] == 'O' && DataCome[(i+1)] == 'K')
	        {
	        	result = 1;
	        }
		}
	}
}

void ESP8266_VidInit ( void ){

	/* Set USART1 CallBack To Receive The Response Of The ESP8266 */
//	USART_vSetCallBack( MUSART_CallBack );
	USARTx_vInit();

	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	//TransmitString_Sync((u16 *)"AT\r\n" );
	TransmitString_Sync((u8 *)"AT\r\n");

	MCAL_STK_delay_ms( 3000 );
	//ValidateCommand();

	/* Clear ESP8266 Buffer */
	ESP8266_VidClearBuffer();

	TransmitString_Sync((u8 *)"AT+CWMODE=3\r\n" );
	MCAL_STK_delay_ms( 3000 );
//	ValidateCommand();

	ESP8266_VidClearBuffer();

	TransmitString_Sync((u8 *)"AT+CIPMODE=0\r\n" );
	MCAL_STK_delay_ms( 3000 );
	//ValidateCommand();

}

void ESP8266_VidConnectToWiFi ( u8 * SSID , u8 * Password ){

	ESP8266_VidClearBuffer();

	TransmitString_Sync((u8 *) "AT+CWJAP=\"" );
	TransmitString_Sync((u8 *) SSID );
	TransmitString_Sync((u8 *) "\",\"" );
	TransmitString_Sync((u8 *) Password);
	TransmitString_Sync((u8 *) "\"\r\n");
	MCAL_STK_delay_ms( 8000 );
//	ValidateCommand();
}


void ESP8266_VidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port ){

	ESP8266_VidClearBuffer();

	TransmitString_Sync((u8 *) "AT+CIPSTART=\"TCP\",\"" );
	TransmitString_Sync((u8 *) Copy_u8Domain );
	TransmitString_Sync((u8 *) "\"," );
	TransmitString_Sync((u8 *) Copy_u8Port );
	TransmitString_Sync((u8 *) "\r\n" );
	MCAL_STK_delay_ms( 2000 );

}

void ESP8266_VidSendHttpReq( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length ){

	ESP8266_VidClearBuffer();

	TransmitString_Sync((u8 *) "AT+CIPSEND=" );
	TransmitString_Sync((u8 *) Copy_u8Length );
	TransmitString_Sync((u8 *) "\r\n" );
	 MCAL_STK_delay_ms( 2000 );

	ESP8266_VidClearBuffer();

	TransmitString_Sync((u8 *) "GET /update?api_key=" );
	TransmitString_Sync((u8 *) Copy_u8Key );
	TransmitString_Sync((u8 *) "&field1=" );
	TransmitString_Sync((u8 *) Copy_u8Data );
	TransmitString_Sync((u8 *) "\r\n" );
	 MCAL_STK_delay_ms( 4000 );

}

u8   ESP8266_u8ReceiveHttpReq( u8 * Copy_u8ChannelID , u8 * Copy_u8Length ){

	ESP8266_VidClearBuffer();

	TransmitString_Sync((u8 *) "AT+CIPSEND=" );
	TransmitString_Sync((u8 *) Copy_u8Length );
	TransmitString_Sync((u8 *) "\r\n" );
	 MCAL_STK_delay_ms( 1000 );

	ESP8266_VidClearBuffer();

	//TransmitString_Sync((u8 *) "GET " );
	TransmitString_Sync((u8 *) Copy_u8ChannelID );
	TransmitString_Sync((u8 *) "\r\n" );
	//TransmitString_Sync((u16 *) "/value.txt\r\n" );
	MCAL_STK_delay_ms( 4000 );

	ESP8266_VidConnectToSrvTcp( (u8 *)DomainURL , (u8 *)"80" );

	/*For yrabiot3.freevar.com ( Value Array Index )*/
	return  DataCome[0] ;

}

void ESP8266_VidClearBuffer ( void ){

	u16 LOC_u8Iterator1 = 0 ;
	Iterator = 0 ;
	result =0;
	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 200 ; LOC_u8Iterator1++ ){
		DataCome[ LOC_u8Iterator1 ] = 0 ;
	}

}

