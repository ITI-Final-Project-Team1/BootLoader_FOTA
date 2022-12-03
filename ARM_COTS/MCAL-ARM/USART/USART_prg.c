/*
 * USART_prg.c
 *
 *  Created on: Nov 13, 2022
 *      Author: Magdy Adel
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../RCC/RCC_int.h"
#include "../NVIC/NVIC_int.h"
#include "../GPIO/GPIO_int.h"

#include "USART_pvt.h"
#include "USART_cfg.h"
#include "USART_int.h"




/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/
USART_Config_t* Global_USART_Config[3] = {NULL, NULL, NULL} ;

/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/


/*
 *=======================================================================
 *						GENERIC FUNCTIONS
 *=======================================================================
 *
*/
static USART_TypeDef * _USARTx_SELECT(enuUSARTx UARTx)
{
	switch (UARTx) {
		case UART1:
			return USART1;
			break;
		case UART2:
			return USART2;
			break;
		case UART3:
			return USART3;
			break;
		default:
			return NULL;
			break;
	}
}



/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
/**================================================================
 * @Fn 				-	MCAL_USART_Init
 * @brief 			-	Initialize USART (Support feature ASYNCH. Only)
 * @param[in]		-	USARTx: where x can be (1..3 depending on device used)
 * @param[in]		-	USART_Config: All USART Configuration EXTI_PinConfig_t
 * @retval 			-	none
 * Note 			-	Support for now Asynch mode & Clock 8Mhz
 */
void MCAL_USART_Init (enuUSARTx UARTx, USART_Config_t * USART_Config )
{
	USART_TypeDef * USARTx = _USARTx_SELECT(UARTx);
	u32 BRR ;//, pclk ;

	//enable the Clock for given USART peripheral
	if (USARTx == USART1)
	{
		Global_USART_Config[0] = USART_Config;
		RCC_vEnableClock(USART1_APB2, APB2);
	}
	else if (USARTx == USART2)
	{
		Global_USART_Config[1] = USART_Config;
		RCC_vEnableClock(USART2_APB1, APB1);
	}
	else if (USARTx == USART3)
	{
		Global_USART_Config[2] = USART_Config;
		RCC_vEnableClock(USART3_APB1, APB1);
	}

	//Enable USART Module
	//	Bit 13 UE: USART enable
	USARTx->CR1 |= (1<<13) ;

	//Enable TX/RX engines according to the USART_Mode Configuration item
	//USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= USART_Config->USART_MODE ;

	//PAYLOAD Width
	//USART_CR1 Bit 12 M: Word length
	USARTx->CR1 |= USART_Config->Payload_Length ;

	//Configuration of parity control bit fields
	//USART_CR1 Bit 9 PS: Parity selection----Bit 10 PCE: Parity control enable
	USARTx->CR1 |= USART_Config->Parity ;

	//Configure the number of stop bits
	//USART_CR2 Bit 13:12 STOP: STOP bits
	USARTx->CR1 |= USART_Config->StopBits ;

	//USART hardware flow control
	//USART_CR3 //Bit 9 CTSE: CTS enable------Bit 8 RTSE: RTS enable
	USARTx->CR1 |= USART_Config->HWFlowCtl ;

	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2,3
	//PCLK1 for USART1
//	if (USARTx == USART1)
//	{
//		pclk = F_CPU;
//	}
//	else
//	{
//		pclk = F_CPU;
//	}
	BRR = USART_BRR_Register(F_CPU, USART_Config->BaudRate);
	USARTx->BRR = BRR;

	//ENABLE / DISABLE Interrupt
	//UASRT_CR1
	if (USART_Config->IRQ_Enable != USART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= USART_Config->IRQ_Enable ;

		//Enable NVIC for USARTx IRQ
		if (USARTx == USART1)
			MCAL_NVIC_vEnableInterrupt(NVIC_USART1_IRQ);
		else if (USARTx == USART2)
			MCAL_NVIC_vEnableInterrupt(NVIC_USART2_IRQ);
		else if (USARTx == USART3)
			MCAL_NVIC_vEnableInterrupt(NVIC_USART3_IRQ);
	}
}


/**================================================================
 * @Fn 				-	MCAL_USART_DeInit
 * @brief 			-	DeInitialize USART (Support feature ASYNCH. Only)
 * @param[in]		-	USARTx: where x can be (1..3 depending on device used)
 * @retval 			-	none
 * Note 			-	Reset the model by RCC
 */
void MCAL_USART_DeInit (enuUSARTx UARTx)
{
	USART_TypeDef * USARTx = _USARTx_SELECT(UARTx);
	if (USARTx == USART1)
	{
		RCC_vRESET(USART1_APB2, APB2);
		MCAL_NVIC_vDisableInterrupt(NVIC_USART1_IRQ);
	}
	else if (USARTx == USART2)
	{
		RCC_vRESET(USART2_APB1, APB1);
		MCAL_NVIC_vDisableInterrupt(NVIC_USART2_IRQ);
	}
	else if (USARTx == USART3)
	{
		RCC_vRESET(USART3_APB1, APB1);
		MCAL_NVIC_vDisableInterrupt(NVIC_USART3_IRQ);
	}
}


/**================================================================
* @Fn				-MCAL_USART_GPIO_Set_Pins
* @brief			-Initialize GPIO Pins
* @param [in] 		-USARTx: where x can be (1..3 depending on device used)
* @retval 			-None
* Note				-Should enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_USART_Init()
*/
void MCAL_USART_GPIO_Set_Pins (enuUSARTx UARTx)
{
	USART_TypeDef * USARTx = _USARTx_SELECT(UARTx);
	GPIO_PinConfig_t PinConfig;
	if (USARTx == USART1)
	{
		//PA9 TX
		PinConfig.GPIO_PinNumber = GPIO_PIN_9;
		PinConfig.GPIO_MODE = GPIO_Mode_AF_OUT_PushPull;
		PinConfig.GPIO_OUTPUT_SPEED = GPIO_Speed_10M;
		MCAL_GPIO_vInit(GPIO_PORTA, &PinConfig);

		//PA10 Rx
		PinConfig.GPIO_PinNumber = GPIO_PIN_10;
		PinConfig.GPIO_MODE = GPIO_MODE_AF_IN;
		MCAL_GPIO_vInit(GPIO_PORTA, &PinConfig);

		//PA11 CTS
		if ( (Global_USART_Config[0]->HWFlowCtl == USART_HWFlowCtl_CTS) || Global_USART_Config[0]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_11;
			PinConfig.GPIO_MODE = GPIO_Mode_IN_Floating;
			MCAL_GPIO_vInit(GPIO_PORTA, &PinConfig);
		}
		//PA12 RTS
		if (Global_USART_Config[0]->HWFlowCtl == USART_HWFlowCtl_RTS || Global_USART_Config[0]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_12;
			PinConfig.GPIO_MODE = GPIO_Mode_AF_OUT_PushPull;
			PinConfig.GPIO_OUTPUT_SPEED = GPIO_Speed_10M;
			MCAL_GPIO_vInit(GPIO_PORTA, &PinConfig);
		}
	}

	else if (USARTx == USART2)
	{
		//PA2 TX
		PinConfig.GPIO_PinNumber = GPIO_PIN_2;
		PinConfig.GPIO_MODE = GPIO_Mode_AF_OUT_PushPull;
		PinConfig.GPIO_OUTPUT_SPEED = GPIO_Speed_10M;
		MCAL_GPIO_vInit(GPIO_PORTA, &PinConfig);

		//PA3 Rx
		PinConfig.GPIO_PinNumber = GPIO_PIN_3;
		PinConfig.GPIO_MODE = GPIO_MODE_AF_IN;
		MCAL_GPIO_vInit(GPIO_PORTA, &PinConfig);

		//PA0 CTS
		if (Global_USART_Config[1]->HWFlowCtl == USART_HWFlowCtl_CTS || Global_USART_Config[1]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_0;
			PinConfig.GPIO_MODE = GPIO_Mode_IN_Floating;
			MCAL_GPIO_vInit(GPIO_PORTA, &PinConfig);
		}
		//PA1 RTS
		if (Global_USART_Config[1]->HWFlowCtl == USART_HWFlowCtl_RTS || Global_USART_Config[1]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_1;
			PinConfig.GPIO_MODE = GPIO_Mode_AF_OUT_PushPull;
			PinConfig.GPIO_OUTPUT_SPEED = GPIO_Speed_10M;
			MCAL_GPIO_vInit(GPIO_PORTA, &PinConfig);
		}
	}

	else if (USARTx == USART3)
	{
		//PB10 TX
		PinConfig.GPIO_PinNumber = GPIO_PIN_10;
		PinConfig.GPIO_MODE = GPIO_Mode_AF_OUT_PushPull;
		PinConfig.GPIO_OUTPUT_SPEED = GPIO_Speed_10M;
		MCAL_GPIO_vInit(GPIOB, &PinConfig);

		//PB11 Rx
		PinConfig.GPIO_PinNumber = GPIO_PIN_11;
		PinConfig.GPIO_MODE = GPIO_MODE_AF_IN;
		MCAL_GPIO_vInit(GPIOB, &PinConfig);

		//PB13 CTS
		if (Global_USART_Config[2]->HWFlowCtl == USART_HWFlowCtl_CTS || Global_USART_Config[2]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_13;
			PinConfig.GPIO_MODE = GPIO_Mode_IN_Floating;
			MCAL_GPIO_vInit(GPIOB, &PinConfig);
		}
		//PB14 RTS
		if (Global_USART_Config[2]->HWFlowCtl == USART_HWFlowCtl_RTS || Global_USART_Config[2]->HWFlowCtl == USART_HWFlowCtl_RTS_CTS)
		{
			PinConfig.GPIO_PinNumber = GPIO_PIN_14;
			PinConfig.GPIO_MODE = GPIO_Mode_AF_OUT_PushPull;
			PinConfig.GPIO_OUTPUT_SPEED = GPIO_Speed_10M;
			MCAL_GPIO_vInit(GPIOB, &PinConfig);
		}
	}

}


/**================================================================
 * @Fn 				-	MCAL_USART_SendData
 * @brief 			-	Send buffer on USART
 * @param[in]		-	USARTx: where x can be (1..3 depending on device used)
 * @param[in]		-	pTxBuffer: Buffer
 * @param[in]		-	PollingEn: Enable or Disable polling
 * @retval 			-	none
 * Note 			-	Should initialize USART first
 * 						When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
 * 						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 * 						because it is replaced by the parity.
 * 						When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
 */
void MCAL_USART_SendData (enuUSARTx UARTx, enum Polling_mechanism PollingEn , u16 *pTxBuffer)
{
	USART_TypeDef * USARTx = _USARTx_SELECT(UARTx);
	u8 i;
	i = (USARTx == USART1)?0 : (USARTx == USART2)?1 : 2 ;

	//wait until TXE flag is set in the SR (is empty)
	if (PollingEn == enable)
		while(! (USARTx->SR & 1<<7));

	//Check the USART_WordLength item for 8bit or 9bit in a frame
	if (Global_USART_Config[i]->Payload_Length == USART_Payload_Length_9B)
	{
		//This is 9bit data transfer
		USARTx->DR = (*pTxBuffer & (u16)0x01FF);

	}else
	{
		//This is 8bit data transfer
		USARTx->DR = (*pTxBuffer & (u16)0xFF);
	}
}


/**================================================================
* @Fn				-MCAL_USART_ReceiveData
* @brief			-Receive Buffer on USART
* @param [in] 		-USARTx: where x can be (1..3 depending on device used)
* @param [in] 		-pRxBuffer Buffer
* @param [in] 		-PollingEn Enable/Disable polling
* @retval 			-None
* Note				-None
*/
void MCAL_USART_ReceiveData (enuUSARTx UARTx, enum Polling_mechanism PollingEn , u16 *pRxBuffer)
{
	USART_TypeDef * USARTx = _USARTx_SELECT(UARTx);
	u8 i;
	i = (USARTx == USART1)?0 : (USARTx == USART2)?1 : 2 ;

	//wait until RXNE flag is set in the SR
	if (PollingEn == enable)
		while(! (USARTx->SR & 1<<5));

	//Check the USART_WordLength item for 8bit or 9bit in a frame
	if (Global_USART_Config[i]->Payload_Length == USART_Payload_Length_9B)
	{
		//This is 9bit data
		if (Global_USART_Config[i]->Parity == USART_Parity_NONE)
		{
			//no parity so All 9bit are considered data
			*((u16*) pRxBuffer) = USARTx->DR ;

		}else
		{
			//Parity is used, so 8bit will be of user data and bit is parity
			*((u16*) pRxBuffer) = ( USARTx->DR & (u8)0xFF ) ;
		}

	}
	else
	{
		//This is 8bit data
		if (Global_USART_Config[i]->Parity == USART_Parity_NONE)
		{
			//no parity so All 8bit are considered data
			*((u16*) pRxBuffer) = USARTx->DR ;

		}else
		{
			//Parity is used, so 7bit will be of user data and bit is parity
			*((u16*) pRxBuffer) = (USARTx->DR & (u8)0x7F );
		}

	}

}





/**================================================================
* @Fn				-MCAL_USART_WAIT_TC
* @brief			-Wait till all data is sent
* @param [in] 		-USARTx: where x can be (1..3 depending on device used)
* @retval 			-None
* Note				-None
*/
void MCAL_USART_WAIT_TC (enuUSARTx UARTx)
{
	USART_TypeDef * USARTx = _USARTx_SELECT(UARTx);
	//wait until TC flag is set in the SR
	while(! (USARTx->SR & 1<<6));
}
void USART1_vClearFlags( void ){

	/* Clear all flags */
	USART1->SR = 0;

}



/*
 *=======================================================================
 *						ISR FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void USART1_IRQHandler(void)
{
	Global_USART_Config[0]->P_IRQ_CallBack();
	/* Clear all flags */
	USART1->SR = 0;


}

void USART2_IRQHandler(void)
{
	Global_USART_Config[1]->P_IRQ_CallBack();
}

void USART3_IRQHandler(void)
{
	Global_USART_Config[2]->P_IRQ_CallBack();
}

