/*
 *=======================================================================
 *						Geniric INCLUDES
 *=======================================================================
 *
*/

#include "../../ARM_COTS/LIB/STD_TYPES.h"
#include "../../ARM_COTS/LIB/BIT_MATH.h"
#include "../../ARM_COTS/MCAL-ARM/RCC/RCC_int.h"
#include "../../ARM_COTS/MCAL-ARM/GPIO/GPIO_int.h"
#include "../../ARM_COTS/MCAL-ARM/STK/STK_int.h"
#include "../../ARM_COTS/MCAL-ARM/NVIC/NVIC_int.h"
#include "../../ARM_COTS/MCAL-ARM/FPEC/FPEC_interface.h"
#include "../../ARM_COTS/MCAL-ARM/USART/USART_interface.h"
#include "../../ARM_COTS/SERVICES/HEX_PARSER/HEX_PARSER.h"

#include "BOOTLOADER.h"
//=======================================================================



//to be replased in ESP8266_PRIVATE.h
#define WifiName_SSID 	"AbdallahSSID"
#define WifiPassword	"AbdallahWifiPassword"
#define DomainURL		"http://fota-bootloader.freevar.com/"
#define UrlGetLINE		"http://fota-bootloader.freevar.com/start_flash.php?config=ok"



/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
#define BTL_TimeOut_us		15000000

/* Current state of the bootloader */
static enuBTL_State currentBTLState;

typedef void (*Function_t)(void);
Function_t CallApp = 0;

enuBOOL needToWrite = false;
enuBOOL appReady = false;
u8 hexRecord[50]; //for hexFile.string
hexRecord_t hexDecoded;
//=======================================================================




/*
 *=======================================================================
 *						Static FUNCTIONS
 *=======================================================================
 *
*/
static void _BTL_vJumpToApp(void)
{
	#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001000;//point to App SP ---firt address of flash in app --- first vector table
	
	CallApp = * (Function_t*)(0x08001004);//APP startup code
	CallApp();
}

// static u8 _BTL_vCheckAppIsReady(void)
// {
	// app_check_address_ptr = (uint32_t *) app_check_address;

    // Read the first location of application section
    // which contains the address of stack pointer
    // If it is 0xFFFFFFFF then the application section is empty
    // if (*app_check_address_ptr == 0xFFFFFFFF) {
        // return 0;
    // }
// }


static void _BTL_voidEraseAppArea(void)
{
	u8 i;
	
	for (i=4;i<64;i++)
	{
		FPEC_xErasePage_ByPN(i);
	}
}


enuBTL_State BTL_enuWaitingState(void)
{
	enuBTL_State currentState;
	u8 isReceived = 0;
	
	//set time out for booting
	MCAL_STK_vSetIntervalSingle((u32 )BTL_TimeOut_us, BTL_enuFinishedState);
	
	//isReceived = USART_vReceiveString_Async( hexRecord );
	/* if received correctly */ 
	if (isReceived)
	{
		//STOP time out for booting
		MCAL_STK_vStopInterval();
		
		//Check if needd to write (first line in hex file)
		if(needToWrite == 1)
		{
			/* erase application region in flash */
			_BTL_voidEraseAppArea();
			needToWrite = 0;		
		}
		appReady = 0;	/*Signal that the application isn't ready*/

		/* application region erased successfully */
		currentState = Burning ; /* move to writing state */

	}
	else /* anything else stay in waiting state */
		currentState = Waiting; 
	
	return currentState;
}



enuBTL_State BTL_enuBurningState(void)
{
	enuBTL_State currentState;
	/* Parse received hex line into record */
	HEXP_Get_RecordData(hexRecord/*	takes one hex record*/, &hexDecoded/*return Data*/);

	if(hexDecoded.record_type == HEXP_EOF ){
		/* if finished writing hex file	signal that the application is ready */
		appReady = 1;
		/* move to finished state */
		currentState = Finished;
	}
	else{
		/* Burn */
		FPEC_xWritePage_ByPA(hexDecoded.data, hexDecoded.byte_count, hexDecoded.address );

		//TO DO
		// OK And send another Record
//		MUSART1_voidTransmit("ok");//ACK +IPD
		//ESP8266_voidSendData(IPserver,"63","fota-bootloader.freevar.com/start_flash.php?config=ok",data);
		
		/* if not finished writing hex file	signal that the application is not ready */
		appReady = 0;
		/* move to finished state */
		currentState = Waiting;
	}
	return currentState;
}


void BTL_enuFinishedState(void)
{
	//lock flash
	FPEC_xLock();
	
	/***** Reset & disable peripheral ***/
	RCC_vDisableClock( USART1_APB2 , APB2 );	/* Disable USART 1 */
	RCC_vDisableClock( IOPA_APB2 , APB2   );	/* Disable GPIOA */


	/* jump to aplication */
	appReady = true;
	_BTL_vJumpToApp();
	
	//return Finished;
}
//=======================================================================




/*
 *=======================================================================
 *						APIS FUNCTIONS Implementations
 *=======================================================================
 *
*/
void BTL_vSetup(void)
{
	/* Initialize RCC to work with 8MHz */
	RCC_vInit();
	RCC_vEnableClock( USART1_APB2 , APB2 );	/* Enable USART 1 */
	RCC_vEnableClock( IOPA_APB2 , APB2   );	/* Enable GPIOA */
	
	/* Configure A9  (Tx1) as Output AFPP @ 2MHz */ 	
	/* Configure A10 (RX1) as input Floating     */
	// GPIO_Config_t USART1_PINs[2] = {
		// {GPIO_PORTA, PIN9 , OUTPUT_2MHZ_AF_PP },
		// {GPIO_PORTA, PIN10, INPUT_FLOATING }
	// };
	// GPIO_vInit(&USART1_PINs[0]);
	// GPIO_vInit(&USART1_PINs[1]);
	
	GPIO_PinConfig_t USART1_PINs[2] = {
		{GPIO_PIN_9, GPIO_Mode_AF_OUT_PushPull , GPIO_Speed_2M },
		{GPIO_PIN_10, GPIO_Mode_IN_Floating ,GPIO_Speed_2M }
	};
	MCAL_GPIO_vInit(GPIOA,&USART1_PINs[1]);
	MCAL_GPIO_vInit(GPIOA,&USART1_PINs[1]);
		


	/* Set USART1 Higer Priority Enable NVIC For USART1 */
	MCAL_NVIC_vSetPriority ( NVIC_USART1_IRQ , 1 , NVIC_GROUP4_SUB0 ) ;
	MCAL_NVIC_vEnableInterrupt (NVIC_USART1_IRQ) ;


	/* Initialize UART */
	USART_vInit();

	/* Setting ESP8266 Mode */
	//ESP8266_VidInit();

	/* Connecting To WIFI Network */
	//ESP8266_VidConnectToWiFi( (u8 *)WifiName_SSID , (u8 *)WifiPassword );
	/* Connecting To subDOMAIN.freevar.com */
	//ESP8266_VidConnectToSrvTcp( (u8 *)DomainURL , (u8 *)"80" );
	//ASK to read first rec
	
	//set need to write flag to erase App section in flash//Write requist
	needToWrite = true;
}


#define state(_statFUN_) 	BTL_enu##_statFUN_##State()
			//(Wating)  	BTL_enuWatingState()
			//				BTL_enuBurningState()
			//				BTL_enuFinishedState

void BTL_vStart(void)
{
	while(currentBTLState != Finished)
	{
		switch(currentBTLState)
		{
			case Waiting : currentBTLState = state(Waiting);  break;
			case Burning : currentBTLState = state(Burning);  break;
			case Finished: break;
		}
	}
	state(Finished); 
}



//=======================================================================



