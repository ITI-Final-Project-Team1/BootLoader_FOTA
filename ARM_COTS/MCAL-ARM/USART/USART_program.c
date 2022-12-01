#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"


static void (* GS_vUSART_CallBack)(void);

u32 G_USART_Data[100] = {0};


void USART_vClearFlags( void ){

	/* Clear all flags */
	USART1->USART_SR = 0;

}

u8 MUSART1_u8ReadDataRegister ( void ){

	return ( USART1->USART_DR );

}

static u32 USART_pow(u32 Copy_32Base, u32 Copy_32Exponent)
{
	u32 Local_u8returnVal = 1, Local_u8index = 0;
	if(Copy_32Base == 0)
	{
		if(Copy_32Exponent == 0)
		{
			Local_u8returnVal = 255;
		}
		else
		{
			Local_u8returnVal = 0;
		}
	}
	else
	{
		for(Local_u8index=0; Local_u8index<Copy_32Exponent; Local_u8index++)
		{
			Local_u8returnVal *= Copy_32Base;
		}
	}
	return Local_u8returnVal;
}



//(X.0->X.4)  or  1.5   or  (X.6->X.9)
static u32 USART_roundRealNumber(f32 Copy_f32RealNumber, u8 Copy_u8precision)
{
	u32 Local_u32RoundedNumber = 0;
	f32 Local_f32Fraction = (Copy_f32RealNumber - (u32)Copy_f32RealNumber);
	u32 Local_u32IntegerValue = Local_f32Fraction* USART_pow(10, Copy_u8precision) ;
	if(Local_u32IntegerValue < 5 * USART_pow(10, Copy_u8precision - 1))
	{
		Local_u32RoundedNumber = (u32)Copy_f32RealNumber;
	}
	else
	{
		Local_u32RoundedNumber = (u32)Copy_f32RealNumber + 1;
	}

	return Local_u32RoundedNumber;
}

static u32 USART1_GetBRRValue(u32 Copy_u32Fcpu, u32 Copy_u32BaudRate)
{
	u32 Local_u32BRRValue = 0x0000;

	f32 Local_f32DIV = ((f32)Copy_u32Fcpu)/((f32)(Copy_u32BaudRate*16));
	u32 Local_u32DIVMantissa = (u32)Local_f32DIV;
	f32 Local_f32DIVFraction = (Local_f32DIV - (f32)Local_u32DIVMantissa) * 16;
	u32 Local_u32DIVFraction = USART_roundRealNumber(Local_f32DIVFraction, 2);
	Local_u32BRRValue = (Local_u32DIVMantissa << 4) | (Local_u32DIVFraction);

	return Local_u32BRRValue;
}


void USART_vInit(void)
{
	//Enable USART
	SET_BIT(USART1->USART_CR1, CR1_UE);
	// Enable the transmitter
	SET_BIT(USART1->USART_CR1, CR1_TE);
	// Enable the Receiver
	SET_BIT(USART1->USART_CR1, CR1_RE);
	// Word length (always 8 bits)
	CLEAR_BIT(USART1->USART_CR1, CR1_M);

	// parity check
	#if USART1_PARITY == ENABLED
		SET_BIT(USART1->USART_CR1, CR1_PCE);
		#if USART1_PARITY_TYPE == EVEN_PARITY
			CLEAR_BIT(USART1->USART_CR1, CR1_PS);
		#elif USART1_PARITY_TYPE == ODD_PARITY
			SET_BIT(USART1->USART_CR1, CR1_PS);
		#endif
	#elif USART1_PARITY == DISABLED
		CLEAR_BIT(USART1->USART_CR1, CR1_PCE);
	#endif

	// stop bits
	#if USART1_STOP_BITS_NO == ONE_STOP_BIT
		CLEAR_BIT(USART1->USART_CR2, CR2_STOP1);
		CLEAR_BIT(USART1->USART_CR2, CR2_STOP2);
	#elif USART1_STOP_BITS_NO == TWO_STOP_BIT
		CLEAR_BIT(USART1->USART_CR2, CR2_STOP1);
		SET_BIT(USART1->USART_CR2, CR2_STOP2);
	#endif

	// Baud Rate
	USART1->USART_BRR = USART1_GetBRRValue(F_CPU, USART1_BAUD_RATE);

	//Reseting Data Register
	USART1->USART_DR = 0x0000;

	// Interrupt Enable/Disable
	#if USART1_INTERRUPT_ENABLE == ENABLED
		SET_BIT(USART1->USART_CR1, CR1_RXNEIE);
//		SET_BIT(USART1->USART_CR1, CR1_TXEIE);
//		SET_BIT(USART1->USART_CR1, CR1_TCIE);
	#else
		CLEAR_BIT(USART1->USART_CR1, CR1_RXNEIE);
		CLEAR_BIT(USART1->USART_CR1, CR1_TXEIE);
		CLEAR_BIT(USART1->USART_CR1, CR1_TCIE);
	#endif

	// The RXNE flag is cleared by writing a zero to it.
	CLEAR_BIT(USART1->USART_SR, SR_RXNE);

}

/**************************************** Sync. ****************************************/

void USART_vTransmitChar_Sync(u8 Copy_u8Data)
{
	// Sending the data
	USART1->USART_DR = Copy_u8Data;
	// polling on the data
	while(!GET_BIT(USART1->USART_SR, SR_TC));
	// The TC bit can be cleared by writing a '0' to it.
	CLEAR_BIT(USART1->USART_SR, SR_TC);
}

// BUG : first char isn't been transmitted
void USART_vTransmitString_Sync(u8* Copy_pu8Data)
{
	u32 Local_u32Index=0;
	while(Copy_pu8Data[Local_u32Index] != '\0')
	{
		USART_vTransmitChar_Sync(Copy_pu8Data[Local_u32Index]);
		Local_u32Index++;
	}
}

// check the return of this function , if 255 it indicates that it doesn't read anything
u8   USART_u8ReceiveChar_Sync(void)
{
	u8 Local_u8ReceivedValue = 0;
	u32 Local_u32Timeout=0;
	// The RXNE flag is cleared by writing a zero to it.
	CLEAR_BIT(USART1->USART_SR, SR_RXNE);
	while((!GET_BIT(USART1->USART_SR, SR_RXNE)) && (Local_u32Timeout < THRESHOLD_VALUE))
	{
		Local_u32Timeout++;
	}
	if(Local_u32Timeout == THRESHOLD_VALUE)
	{
		Local_u8ReceivedValue = 255;
	}
	else
	{
		Local_u8ReceivedValue = (u8)(USART1->USART_DR);
	}
	return Local_u8ReceivedValue;
}


void USART_vReceiveString_Sync(u8* Copy_pu8Data/* return data */)
{
	u8 Localu8received = 0;
	u16 Local_u16Index = 0;
	while((Localu8received = USART_u8ReceiveChar_Sync())!= CARRIAGE_NUMBER) // Receiving process doesn't finished, so receive more
	{
		Copy_pu8Data[Local_u16Index] = Localu8received;
		Local_u16Index++;
	}
	Copy_pu8Data[Local_u16Index] = '\0';
}


/**************************************** Async. ****************************************/

void USART_vTransmitChar_Async(u8 Copy_u8Data)
{

	if(USART1->USART_SR, SR_TXE)
	{
		// Sending the data
		USART1->USART_DR = Copy_u8Data;

	}

//	MCAL_NVIC_vEnableInterrupt(37);

}

u8   USART_u8ReceiveChar_Async(void)
{

	return (u8)(USART1->USART_DR);
}

void USART_vTransmitString_Async(u8* Copy_pu8Data)
{
	(void)Copy_pu8Data;
//	u32 Local_u32Index=0;
//	while(Copy_pu8Data[Local_u32Index] != '\0')
//	{
//		USART_vTransmitChar(Copy_pu8Data[Local_u32Index]);
//		Local_u32Index++;
//	}
}

u8 USART_vReceiveString_Async(void)
{
	// TODO:
	return 5;
}


void USART_vSetCallBack(void (* Pf_vUSART_CallBack)(void))
{
	GS_vUSART_CallBack = Pf_vUSART_CallBack;
}

void USART1_IRQHandler(void)
{
	if(GS_vUSART_CallBack != NULL)
	{
		GS_vUSART_CallBack();
	}
	// The RXNE flag is cleared by writing a zero to it.
	CLEAR_BIT(USART1->USART_SR, SR_RXNE);
	// The TC bit can be cleared by writing a '0' to it.
	CLEAR_BIT(USART1->USART_SR, SR_TC);
}









