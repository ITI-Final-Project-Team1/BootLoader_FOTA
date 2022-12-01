/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : FPEC  				******************/
/*************	 Date    : 21 Nov 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/



#ifndef MCAL_FPEC_FPEC_INTERFACE_H_
#define MCAL_FPEC_FPEC_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

//void FPEC_vInit(void);

Err_t FPEC_xLock(void);

Err_t FPEC_xUnlock(void);

Err_t FPEC_xEraseMass(void);

Err_t FPEC_xErasePage_ByPN(u8 Copy_u8PageNumber);

Err_t FPEC_xErasePage_ByPA(u32 Local_u32PageAddress);

Err_t FPEC_xWritePage_ByPN(u16* Copy_u16Data, u8 Copy_u8Length, u8 Copy_u8PageNumber);

Err_t FPEC_xWritePage_ByPA(u16* Copy_u16Data, u8 Copy_u8Length, u32 Local_u32PageAddress);

// what Actually we will use directly:

// TODO: Include the Unlocking and Erasing operations before writing and Lock after writing
Err_t FPEC_xWriteFullPage(u16* Copy_u16Data, u8 Copy_u8Length, u8 Copy_u8PageNumber);


#endif /* MCAL_FPEC_FPEC_INTERFACE_H_ */
