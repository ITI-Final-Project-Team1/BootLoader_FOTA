/*
 *=======================================================================
 *						Generic INCLUDES
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
#include "../../ARM_COTS/MCAL-ARM/USART/USART_int.h"
#include "../../ARM_COTS/SERVICES/HEX_PARSER/HEX_PARSER.h"
#include "../../ARM_COTS/HAL/ESP8266/ESP8266_INTERFACE.h"
#include "../../ARM_COTS/SERVICES/HEX_PARSER/ESP_PARSER.h"

#include "BOOTLOADER.h"
//=======================================================================



/*
 *=======================================================================
 *						GENERAL VARIABLES
 *=======================================================================
 *
*/
#define BTL_TimeOut_us		15000000

/* Current state of the bootloader */
static enuBTL_State currentBTLState;

typedef void (*Function_t)(void);
Function_t CallApp = NULL;

volatile enuBOOL needToWrite = false;
enuBOOL appReady = false;

extern volatile u8 DataCome[200]; //for hexFile.string
//u8 data[60] ={0};
//u8  u8RecBuffer[100] = {0};


ESPResponse_t ExtractedData = {
        .Data = {0},
        .DataLength = 0
};
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

	SCB_VTOR = 0x08002000;//point to App SP ---first address of flash in app --- first vector table
	
	CallApp = * (Function_t*)(0x08002004);//APP startup code
	CallApp();
}


static void _BTL_voidEraseAppArea(void)
{
	u8 i;
	
	for (i=8;i<64;i++)
	{
		FPEC_xErasePage_ByPN(i);
	}
}


enuBTL_State BTL_enuWaitingState(void)
{
	enuBTL_State currentState;
	u8 isReceived = 0;
	MCAL_GPIO_vWritePin(GPIOA , GPIO_PIN_3, GPIO_PIN_HIGH);
	//ASK for record
	isReceived = ESP8266_u8ReceiveHttpReq((u8 *)UrlGetLINE,(u8 *)"66");
	/* if received correctly */ 
	if (isReceived=='+')
	{
		MCAL_GPIO_vWritePin(GPIOA , GPIO_PIN_3, GPIO_PIN_LOW);
		//STOP time out for booting
		MCAL_STK_vStopInterval();
		
		//Check if needed to write (first line in hex file)
		if(needToWrite == true)
		{
			/* erase application region in flash */
			_BTL_voidEraseAppArea();
			needToWrite = 0;		
		}
		appReady = 0;	/*Signal that the application isn't ready*/
		isReceived =0;
		/* application region erased successfully */
		currentState = Burning ; /* move to writing state */

	}
	else /* anything else stay in waiting state */
	{
		currentState = Waiting; 
		MCAL_GPIO_vWritePin(GPIOA , GPIO_PIN_3, GPIO_PIN_LOW);
	}
	return currentState;
}



enuBTL_State BTL_enuBurningState(void)
{
	enuBTL_State currentState;
	ESP_vParseData((u8* volatile)DataCome, &ExtractedData);
	/* Parse received hex line into record */
	HEXP_Get_RecordData(ExtractedData.Data/*takes one hex record*/, &hexDecoded/*return Data*/);
	MCAL_GPIO_vWritePin(GPIOA , GPIO_PIN_3, GPIO_PIN_LOW);
	
	if(hexDecoded.record_type == HEXP_EOF ){
		
		/* if finished writing hex file	signal that the application is ready */
		appReady = 1;
		/* move to finished state */
		currentState = Finished;
	}
	else{
		/* Burn */
		FPEC_xWritePage_ByPA(hexDecoded.data, hexDecoded.byte_count, hexDecoded.address);

		//TODO
		// OK And send another Record
//		MUSART1_voidTransmit("ok");//ACK +IPD
		//ASK to read first rec
		//ESP8266_u8ReceiveHttpReq((u8 *)UrlGetLINE,(u8 *)"53");
		//ESP8266_voidSendData(IPserver,"63","fota-bootloader.freevar.com/start_flash.php?config=ok",data);
		ESP8266_u8ReceiveHttpReq((u8 *)UrlRETRIVELINE,(u8 *)"68");
		
		/* if not finished writing hex file	signal that the application is not ready */
		appReady = 0;
		/* move to finished state */
		currentState = Waiting;
		//set time out for booting
		MCAL_STK_vSetIntervalSingle((u32 )BTL_TimeOut_us, BTL_enuFinishedState);
	}
	return currentState;
}


void BTL_enuFinishedState(void)
{
	//lock flash
	FPEC_xLock();
	MCAL_GPIO_vWritePin(GPIOA , GPIO_PIN_3, GPIO_PIN_LOW);
	
	/***** Reset & disable peripheral ***/
	RCC_vDisableClock( USART1_APB2 , APB2 );	/* Disable USART 1 */
	RCC_vDisableClock( IOPA_APB2 , APB2   );	/* Disable GPIOA */


	/* jump to aplication */

	if(appReady == true)
	{
		_BTL_vJumpToApp();
	}
	
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

	GPIO_PinConfig_t led = {GPIO_PIN_3, GPIO_Mode_OUT_PushPull , GPIO_Speed_2M };	
	MCAL_GPIO_vInit(GPIOA,&led);
	
	MCAL_GPIO_vWritePin(GPIOA , GPIO_PIN_3, GPIO_PIN_HIGH);

	/* Set USART1 Higer Priority Enable NVIC For USART1 */
	MCAL_NVIC_vSetPriority ( NVIC_USART1_IRQ , 1 , NVIC_GROUP4_SUB0 ) ;

	/* Setting ESP8266 Mode */
	ESP8266_VidInit();

	/* Connecting To WIFI Network */
	ESP8266_VidConnectToWiFi( (u8 *)WifiName_SSID , (u8 *)WifiPassword );
	/* Connecting To subDOMAIN.freevar.com */
	ESP8266_VidConnectToSrvTcp( (u8 *)DomainURL , (u8 *)"80" );
	
	//ASK to read first rec
	ESP8266_u8ReceiveHttpReq((u8 *)UrlRestartLINE,(u8 *)"56");

	//set time out for booting
	MCAL_STK_vSetIntervalSingle((u32 )BTL_TimeOut_us, BTL_enuFinishedState);

	//set need to write flag to erase App section in flash//Write requist
	needToWrite = true;
	currentBTLState = Waiting;
}


#define state(_statFUN_) 	BTL_enu##_statFUN_##State()
			//(Waiting)  	BTL_enuWaitingState()
	        //(Burning)		BTL_enuBurningState()
			//(Finished)	BTL_enuFinishedState()

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



