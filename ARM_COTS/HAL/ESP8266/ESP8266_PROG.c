/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL-ARM/USART/USART_interface.h"

#include "ESP8266_INTERFACE.h"

#include "DELAY_INTERFACE.h"

void MUSART_CallBack ( void );
u8 volatile Iterator = 0  ;
u8 volatile DataCome[200] ;
void MUSART_CallBack ( void ){

	/* Receive ESP8266 Response */
	DataCome[ Iterator ] = MUSART1_u8ReadDataRegister();
	/* ------------------ */
	Iterator++;
	USART_vClearFlags();

}

void ESP8266_VidInit ( void ){

	/* Set USART1 CallBack To Receive The Response Of The ESP8266 */
	USART_vSetCallBack( MUSART_CallBack );

	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	USART_vTransmitString_Sync( (u8 *)"AT\r\n" );

	_delay_ms( 3000 );

	/* Clear ESP8266 Buffer */
	ESP8266_VidClearBuffer();

	USART_vTransmitString_Sync( (u8 *)"AT+CWMODE=3\r\n" );
	_delay_ms( 3000 );

	ESP8266_VidClearBuffer();

	USART_vTransmitString_Sync( (u8 *)"AT+CIPMODE=0\r\n" );
	_delay_ms( 3000 );

}

void ESP8266_VidConnectToWiFi ( u8 * SSID , u8 * Password ){

	ESP8266_VidClearBuffer();

	USART_vTransmitString_Sync( (u8 *) "AT+CWJAP=\"" );
	USART_vTransmitString_Sync( (u8 *) SSID );
	USART_vTransmitString_Sync( (u8 *) "\",\"" );
	USART_vTransmitString_Sync( (u8 *) Password);
	USART_vTransmitString_Sync( (u8 *) "\"\r\n");
	_delay_ms( 8000 );

}


void ESP8266_VidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port ){

	ESP8266_VidClearBuffer();

	USART_vTransmitString_Sync( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
	USART_vTransmitString_Sync( (u8 *) Copy_u8Domain );
	USART_vTransmitString_Sync( (u8 *) "\"," );
	USART_vTransmitString_Sync( (u8 *) Copy_u8Port );
	USART_vTransmitString_Sync( (u8 *) "\r\n" );
	_delay_ms( 2000 );

}

void ESP8266_VidSendHttpReq( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length ){

	ESP8266_VidClearBuffer();

	USART_vTransmitString_Sync( (u8 *) "AT+CIPSEND=" );
	USART_vTransmitString_Sync( (u8 *) Copy_u8Length );
	USART_vTransmitString_Sync( (u8 *) "\r\n" );
	_delay_ms( 4000 );

	ESP8266_VidClearBuffer();

	USART_vTransmitString_Sync( (u8 *) "GET /update?api_key=" );
	USART_vTransmitString_Sync( (u8 *) Copy_u8Key );
	USART_vTransmitString_Sync( (u8 *) "&field1=" );
	USART_vTransmitString_Sync( (u8 *) Copy_u8Data );
	USART_vTransmitString_Sync( (u8 *) "\r\n" );
	_delay_ms( 20000 );

}

u8   ESP8266_u8ReceiveHttpReq( u8 * Copy_u8ChannelID , u8 * Copy_u8Length ){

	ESP8266_VidClearBuffer();

	USART_vTransmitString_Sync( (u8 *) "AT+CIPSEND=" );
	USART_vTransmitString_Sync( (u8 *) Copy_u8Length );
	USART_vTransmitString_Sync( (u8 *) "\r\n" );
	_delay_ms( 4000 );

	ESP8266_VidClearBuffer();

	//USART_vTransmitString_Sync( (u8 *) "GET http://" );
	USART_vTransmitString_Sync( (u8 *) Copy_u8ChannelID );
	//USART_vTransmitString_Sync( (u8 *) "/value.txt\r\n" );
	_delay_ms( 20000 );

	ESP8266_VidConnectToSrvTcp( (u8 *)"162.253.155.226" , (u8 *)"80" );

	/*For yrabiot3.freevar.com ( Value Array Index )*/
	return  DataCome[82] ;

}

void ESP8266_VidClearBuffer ( void ){

	u8 LOC_u8Iterator1 = 0 ;
	Iterator     = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 150 ; LOC_u8Iterator1++ ){

		DataCome[ LOC_u8Iterator1 ] = 0 ;

	}

}
