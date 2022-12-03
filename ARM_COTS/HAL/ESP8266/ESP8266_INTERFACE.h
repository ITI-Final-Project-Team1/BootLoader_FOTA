/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/


#ifndef ESP8266_INTERFACE_H_
#define ESP8266_INTERFACE_H_


//to be replased in ESP8266_PRIVATE.h
#define WifiName_SSID 	"printer"
#define WifiPassword	"AEI#issa292955$$"
#define DomainURL		"172.107.162.12"
#define UrlGetLINE		"GET http://fota-bootloader.freevar.com/start_flash.php?config=ok" //length : 68
#define UrlRETRIVELINE	"GET http://fota-bootloader.freevar.com/start_flash.php?config=none" //length : 66
#define UrlRestartLINE	"GET http://fota-bootloader.freevar.com/start_flash.php" //length : 56


void ESP8266_VidInit            ( void                                                    ) ;
void ESP8266_VidConnectToWiFi   ( u8 * SSID , u8 * Password                               ) ;
void ESP8266_VidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port                   ) ;
void ESP8266_VidSendHttpReq     ( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length ) ;
u8   ESP8266_u8ReceiveHttpReq   ( u8 * Copy_u8ChannelID , u8 * Copy_u8Length              ) ;

void ESP8266_VidClearBuffer     ( void                                                    ) ;


#endif /* ESP8266_INTERFACE_H_ */
