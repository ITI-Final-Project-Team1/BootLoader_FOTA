/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : SERVICES				******************/
/*************	 SWC   	 : ESP_PARSER			******************/
/*************	 Date    : 21 Nov 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ESP_PARSER.h"

#define ESP_STARTING_DELIMITER		"+IPD,"
#define ESP_SEPERATOR_DELIMITER		':'


//pass the smallest one first
static u8 ESP_u8EqualStrings(u8* Copy_pu8String1, u8* Copy_pu8String2)
{
	u8 Local_u8Status   = 1;
	u16 Local_u16Index1 = 0;
	while( Copy_pu8String1[Local_u16Index1] != '\0' )
	{
		if(Copy_pu8String1[Local_u16Index1] != Copy_pu8String2[Local_u16Index1])
		{
			Local_u8Status = 0;
			break;
		}
		else
		{
			Local_u16Index1++;
		}
	}
	return Local_u8Status;
}





static u8 ESP_u8ASCII_To_HEX(u8 Copy_u8HexValue)
{
	u8 Local_u8HexValue = 0;


	if(Copy_u8HexValue >= '0' && Copy_u8HexValue <= '9')
	{
		Local_u8HexValue = Copy_u8HexValue - '0';
	}
	else if(Copy_u8HexValue >= 'A' && Copy_u8HexValue <= 'F')
	{
		Local_u8HexValue = Copy_u8HexValue - 'A' + 10;
	}
	else if(Copy_u8HexValue >= 'a' && Copy_u8HexValue <= 'f')
	{
		Local_u8HexValue = Copy_u8HexValue - 'a' + 10;
	}
	else
	{
		// entered hex value is invalid
		Local_u8HexValue = -1;//255
	}

	return Local_u8HexValue;
}

static u32 ESP_u32Pow(u32 Copy_32Base, u32 Copy_32Exponent)
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

// Not Used
//u32 ESP_u32ReverseNumber(u32 Copy_u32Number) // 654321 => 123456
//{
//    u32 Local_u32Result = 0, Local_u32Temp = Copy_u32Number, Local_u32LastNumber = 0, Local_u32NumberLength = 0;
//    // get the Number Length first
//    while(Local_u32Temp)
//    {
//        Local_u32Temp = Local_u32Temp/10;
//        Local_u32NumberLength++;
//    }
//
//    for(u32 Local_u32Index=Local_u32NumberLength; Local_u32Index>0; Local_u32Index--)
//    {
//        Local_u32LastNumber = Copy_u32Number%10;
//        Local_u32Result += Local_u32LastNumber * ESP_u32Pow(10, Local_u32Index-1);
//        Copy_u32Number = Copy_u32Number/10;
//    }
//    return Local_u32Result;
//}


/*
 *	// +IPD,1:1CLOSED
 * - Parsing (+IPD,1:1CLOSED)->  to extract length of data and data
 * -         (+IPD,)                (1)                  (:)                     (1)                        (CLOSED)
 * -  (STARTING delimiter)   (length of data)    (seperator delimiter)   (Actual received data)        (ENDING delimiter)
 *
 */


void ESP_vParseData(u8* volatile Copy_pu8Response, ESPResponse_t* ExtractedData)
{
    u8 Local_u8Index = 0, Local_u8Counter = 0, Local_u8Iterator = 0;
    u32 Local_u32DL = 0, Local_u32CounterD = 0, Local_u32CounterDTemp = 0;
    if(ESP_u8EqualStrings((u8*)ESP_STARTING_DELIMITER, Copy_pu8Response))
    {
        // loop until reaching the ESP_SEPERATOR_DELIMITER to get the DL digits count
        while(Copy_pu8Response[Local_u8Index + 5] != ESP_SEPERATOR_DELIMITER)
        {
            Local_u8Counter++;
            Local_u8Index++;
        }
        Local_u8Index = 0;
        for(u8 Local_u8i = Local_u8Counter; Local_u8i>0; Local_u8i--)// 123 => 321
        {
            Local_u32DL += ESP_u8ASCII_To_HEX(Copy_pu8Response[Local_u8Index + 5]) * ESP_u32Pow(10, Local_u8i-1);
            Local_u8Index++;
        }
        ExtractedData->DataLength = Local_u32DL;
        Local_u8Index = 0;

        // loop until reaching the HEXP_ENDING_DELIMITER to get the Actual Data digits count
        while( !((Copy_pu8Response[ Local_u8Index + 5 + Local_u8Counter + 1] == 'C') && (Copy_pu8Response[ Local_u8Index + 5 + Local_u8Counter + 2] == 'L')) )
        {
            Local_u32CounterD++;
            Local_u8Index++;
        }
        //printf("%d\n", Local_u32CounterD);
        // loop until the Actual Data digits count becomes zero
        Local_u8Index = 0;
        Local_u32CounterDTemp = Local_u32CounterD;
        while(Local_u32CounterDTemp--)
        {
            ExtractedData->Data[Local_u8Iterator] = Copy_pu8Response[ Local_u8Index + 5 + Local_u8Counter + 1 + Local_u8Iterator];
            Local_u8Iterator++;
        }

//        for(u8 i=0; i<Local_u32CounterD;i++)
//        {
//            printf("%d\n", ExtractedData->Data[i]);
//        }
    }
    else
    {
        // Error : Not Starting with the ESP_STARTING_DELIMITER
        //printf("%s\n", "Abdallah Issa is Sad");
    	// For Dubugging purposes
    }
}
