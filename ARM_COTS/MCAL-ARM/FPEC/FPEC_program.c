/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : FPEC  				******************/
/*************	 Date    : 21 Nov 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"


//void FPEC_vInit(void)
//{
//	FPEC->FPEC_ACR = 0x00; // disable prefetch buffer + latency : 000 Zero wait state, if 0 < SYSCLK <= 24 MHz
//}




Err_t FPEC_xLock(void)
{
	Err_t Local_returnVal = ERR;

	SET_BIT(FPEC->FPEC_CR, CR_LOCK);
	if(GET_BIT(FPEC->FPEC_CR, CR_LOCK))
	{
		Local_returnVal = NO_ERR;
	}

	return Local_returnVal;
}



Err_t FPEC_xUnlock(void)
{
	Err_t Local_returnVal = ERR;

	if(GET_BIT(FPEC->FPEC_CR, CR_LOCK))
	{
		FPEC->FPEC_KEYR = FPEC_KEY1;
		FPEC->FPEC_KEYR = FPEC_KEY2;
		Local_returnVal = NO_ERR;
	}
	return Local_returnVal;
}




Err_t FPEC_xEraseMass(void)
{
	Err_t Local_returnVal = NO_ERR;

	//Check that no Flash memory operation is ongoing
	while(GET_BIT(FPEC->FPEC_SR, SR_BSY));
	// Set the MER bit to Erase of all user pages chosen
	SET_BIT(FPEC->FPEC_CR, CR_MER);
	// Set the STRT bit to triggers an ERASE operation
	SET_BIT(FPEC->FPEC_CR, CR_STRT);
	// Wait for the BSY bit to be reset
	while(GET_BIT(FPEC->FPEC_SR, SR_BSY));

	// Reset the MER bit
	CLEAR_BIT(FPEC->FPEC_CR, CR_MER);

	return Local_returnVal;
}

Err_t FPEC_xErasePage_ByPN(u8 Copy_u8PageNumber)
{
	Err_t Local_returnVal = ERR;
	u32 Local_u32PageAddress = (u32)(Copy_u8PageNumber * 1024 + FPEC_BASE_PAGE_ADDRESS);

	if(Local_u32PageAddress >= FPEC_BASE_PAGE_ADDRESS && Local_u32PageAddress<= FPEC_ENDING_PAGE_ADDRESS)
	{
		// Check that no Flash memory operation is ongoing
		while(GET_BIT(FPEC->FPEC_SR, SR_BSY));
		// Set the PER bit that means that the Page Erase chosen.
		SET_BIT(FPEC->FPEC_CR, CR_PER);
		// Program the FLASH_AR register to select a page to erase
		FPEC->FPEC_AR = (u32)(Copy_u8PageNumber * 1024 + FPEC_BASE_PAGE_ADDRESS);
		// Set the STRT bit to triggers an ERASE operation
		SET_BIT(FPEC->FPEC_CR, CR_STRT);
		// Wait for the BSY bit to be reset
		while(GET_BIT(FPEC->FPEC_SR, SR_BSY));

		if((*(volatile u32 *)Local_u32PageAddress) == 0xFFFFFFFF) // Check the page if it's cleared
		{
			Local_returnVal = NO_ERR;
		}
		else
		{
			Local_returnVal = ERR;
		}
		// Reset the PER bit
		CLEAR_BIT(FPEC->FPEC_CR, CR_PER);
	}
	else
	{
		Local_returnVal = ERR;
	}
	return Local_returnVal;
}


Err_t FPEC_xErasePage_ByPA(u32 Local_u32PageAddress)
{
	Err_t Local_returnVal = ERR;

	if(Local_u32PageAddress >= FPEC_BASE_PAGE_ADDRESS && Local_u32PageAddress<= FPEC_ENDING_PAGE_ADDRESS)
	{
		// Check that no Flash memory operation is ongoing
		while(GET_BIT(FPEC->FPEC_SR, SR_BSY));
		// Set the PER bit that means that the Page Erase chosen.
		SET_BIT(FPEC->FPEC_CR, CR_PER);
		// Program the FLASH_AR register to select a page to erase
		FPEC->FPEC_AR = Local_u32PageAddress;
		// Set the STRT bit to triggers an ERASE operation
		SET_BIT(FPEC->FPEC_CR, CR_STRT);
		// Wait for the BSY bit to be reset
		while(GET_BIT(FPEC->FPEC_SR, SR_BSY));

		if((*(volatile u32 *)Local_u32PageAddress) == 0xFFFFFFFF) // Check the page if it's cleared
		{
			Local_returnVal = NO_ERR;
		}
		else
		{
			Local_returnVal = ERR;
		}
		// Reset the PER bit
		CLEAR_BIT(FPEC->FPEC_CR, CR_PER);
	}
	else
	{
		Local_returnVal = ERR;
	}
	return Local_returnVal;
}


Err_t FPEC_xWritePage_ByPN(u16* Copy_u16Data, u8 Copy_u8Length, u8 Copy_u8PageNumber)
{
	Err_t Local_returnVal = ERR;
	u8 Local_u8Index = 0;
	u32 Local_u32PageAddress = (u32)(Copy_u8PageNumber * 1024 + FPEC_BASE_PAGE_ADDRESS);
	if(Local_u32PageAddress >= FPEC_BASE_PAGE_ADDRESS && Local_u32PageAddress<= FPEC_ENDING_PAGE_ADDRESS)
	{
		// Wait for the BSY bit to be reset
		while(GET_BIT(FPEC->FPEC_SR, SR_BSY));
		// Set the PG bit that means that the Flash programming chosen.
		SET_BIT(FPEC->FPEC_CR, CR_PG);
		for(Local_u8Index=0; Local_u8Index<Copy_u8Length; Local_u8Index++)
		{
			SET_BIT(FPEC->FPEC_SR, SR_EOP);
			// Perform the data write (half-word) at the desired address.
			(*(volatile u16 *)(Local_u32PageAddress)) = Copy_u16Data[Local_u8Index];
			// incrementing with 2 bytes (half-word)
			Local_u32PageAddress += 2;
			// Wait for the BSY bit to be reset
			while(GET_BIT(FPEC->FPEC_SR, SR_BSY));
		}
		// Reset the PG bit
		CLEAR_BIT(FPEC->FPEC_CR, CR_PG);

		Local_returnVal = NO_ERR;
	}
	else
	{
		Local_returnVal = ERR;
	}
	return Local_returnVal;
}


Err_t FPEC_xWritePage_ByPA(u16* Copy_u16Data, u8 Copy_u8Length, u32 Local_u32PageAddress)
{
	Err_t Local_returnVal = ERR;
	u8 Local_u8Index = 0;
	if(Local_u32PageAddress >= FPEC_BASE_PAGE_ADDRESS && Local_u32PageAddress<= FPEC_ENDING_PAGE_ADDRESS)
	{
		// Wait for the BSY bit to be reset
		while(GET_BIT(FPEC->FPEC_SR, SR_BSY));
		// Set the PG bit that means that the Flash programming chosen.
		SET_BIT(FPEC->FPEC_CR, CR_PG);
		for(Local_u8Index=0; Local_u8Index<Copy_u8Length; Local_u8Index++)
		{
			SET_BIT(FPEC->FPEC_SR, SR_EOP);
			// Perform the data write (half-word) at the desired address.
			(*(volatile u16 *)(Local_u32PageAddress)) = Copy_u16Data[Local_u8Index];
			// incrementing with 2 bytes (half-word)
			Local_u32PageAddress += 0x02;
			// Wait for the BSY bit to be reset
			while(GET_BIT(FPEC->FPEC_SR, SR_BSY));
		}
		// Reset the PG bit
		CLEAR_BIT(FPEC->FPEC_CR, CR_PG);

		Local_returnVal = NO_ERR;
	}
	else
	{
		Local_returnVal = ERR;
	}
	return Local_returnVal;
}









