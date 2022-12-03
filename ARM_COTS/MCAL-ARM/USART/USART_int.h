/*
 * USART_int.h
 *
 *  Created on: Nov 13, 2022
 *      Author: Magdy Adel
 */

#ifndef MCAL_ARM_USART_USART_INT_H_
#define MCAL_ARM_USART_USART_INT_H_

#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif


/*
 *=======================================================================
 *				User type definitions (Configuration structures)
 *=======================================================================
 *
*/
typedef struct{
	u8 USART_MODE			;//Specifies TX/RX Enable\Disable
								//this parameter must be set based on @ref USART_MODE_define

	u32 BaudRate			;//This member configures the UART communication baud rate
								//this parameter must be set based on @ref USART_BaudRate_define

	u16 Payload_Length		;//Specifies the number of data bits transmitted or received in a frame.
								//this parameter must be set based on @ref USART_Payload_Length_define

	u8 Parity				;//Specifies the Parity Mode
								//this parameter must be set based on @ref USART_Parity_define

	u8 StopBits			;//Specifies the number of stop bits transmitted
								//this parameter must be set based on @ref USART_StopBits_define

	u16 HWFlowCtl			;//Specifies whether the hardware flow control mode is enable/disable
								//this parameter must be set based on @ref USART_HWFlowCtl_define

	u8 IRQ_Enable			;//Enable or Disable UART IRQ TX/RX
								//this parameter must be set based on @ref USART_IRQ_Enable_define

	void (* P_IRQ_CallBack)(void);			//Set the C Function() which will be called once the IRQ Happen

}USART_Config_t;


/*
 *=======================================================================
 *						Macros Configuration References
 *=======================================================================
 *
*/
//@ref USART_MODE_define
#define USART_MODE_RX						(u32)(1<<2) //Bit 2 RE: Receiver enable
#define USART_MODE_TX						(u32)(1<<3) //Bit 3 TE: Transmitter enable
#define USART_MODE_TX_RX					(u32)((1<<2) | (1<<3))

//@ref USART_BaudRate_define
#define USART_BaudRate_2400					2400
#define USART_BaudRate_9600					9600
#define USART_BaudRate_19200				19200
#define USART_BaudRate_57600				57600
#define USART_BaudRate_115200				115200
#define USART_BaudRate_230400				230400
#define USART_BaudRate_460800				460800
#define USART_BaudRate_921600				921600
#define USART_BaudRate_2250000				2250000
#define USART_BaudRate_4500000				4500000

//@ref USART_Payload_Length_define
//Bit 12 M: Word length
#define USART_Payload_Length_8B				(u16)(0)		 //0: 1 Start bit, 8 Data bits, n Stop bit
#define USART_Payload_Length_9B				(u16)(1<<12)//1: 1 Start bit, 9 Data bits, n Stop bit

//@ref USART_Parity_define
//Bit 9 PS: Parity selection----Bit 10 PCE: Parity control enable
#define USART_Parity_NONE					(u32)(0)
#define USART_Parity_EVEN					(u32)(1<<10)
#define USART_Parity_ODD					(u32)((1<<10) | (1<<9))

//@ref USART_StopBits_define
//Bits 13:12 STOP: STOP bits
#define USART_StopBits__half				(u32)(1<<12)
#define USART_StopBits__1					(u32)(0)
#define USART_StopBits__1_half				(u32)(3<<12)
#define USART_StopBits__2					(u32)(2<<12)

//@ref USART_HWFlowCtl_define
//Bit 9 CTSE: CTS enable------Bit 8 RTSE: RTS enable
#define USART_HWFlowCtl_NONE				(u316)(0)
#define USART_HWFlowCtl_RTS					(u16)(1<<8)
#define USART_HWFlowCtl_CTS					(u16)(1<<9)
#define USART_HWFlowCtl_RTS_CTS				(u16)(1<<8 | 1<<9)

//@ref USART_IRQ_Enable_define
//Table 196. USART interrupt requests
#define USART_IRQ_Enable_NONE				(u32)(0)
#define USART_IRQ_Enable_TXE				(u32)(1<<7) //Transmit data register empty
#define USART_IRQ_Enable_TC					(u32)(1<<6) //Transmission complete
#define USART_IRQ_Enable_RXNEIE				(u32)(1<<5) //Received data ready to be read & Overrun error detected
#define USART_IRQ_Enable_PE					(u32)(1<<8) //Parity error


enum Polling_mechanism
{
	enable,
	disable
};

typedef enum {
	UART1,
	UART2,
	UART3
}enuUSARTx;





/*
* ===================================================================================
* 						APIs Supported by "MCAL USART DRIVER"
* ===================================================================================
*/
void MCAL_USART_Init (enuUSARTx UARTx, USART_Config_t * USART_Config );
void MCAL_USART_DeInit (enuUSARTx UARTx);

void MCAL_USART_GPIO_Set_Pins (enuUSARTx UARTx);

void MCAL_USART_SendData (enuUSARTx UARTx, enum Polling_mechanism PollingEn , u16 *pTxBuffer);
void MCAL_USART_ReceiveData (enuUSARTx UARTx, enum Polling_mechanism PollingEn , u16 *pRxBuffer);

void MCAL_USART_WAIT_TC (enuUSARTx UARTx);
void USART1_vClearFlags( void );



#ifdef __cplusplus // intrinsic macro
extern "C" {
#endif


#endif /* MCAL_ARM_USART_USART_INT_H_ */
