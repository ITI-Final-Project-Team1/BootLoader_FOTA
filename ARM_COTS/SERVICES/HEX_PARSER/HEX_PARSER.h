/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : SERVICES				******************/
/*************	 SWC   	 : HEX_PARSER			******************/
/*************	 Date    : 21 Nov 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/


#ifndef SERVICES_HEX_PARSER_HEX_PARSER_H_
#define SERVICES_HEX_PARSER_HEX_PARSER_H_

#include "../../LIB/STD_TYPES.h"


// :100000000050002021020008270200082B020008EF
//   (:)        (10)               (0000)            (00)        (0050002021020008270200082B020008)     (EF)        (\n)
// (start)   (Byte Count)     (Relative Address)  (Record Type)				(Data)                    (CheckSum)    (End)
// CheckSum Calculation =>  CheckSum = 256 - ( sum( Byte Values) ) MOD 256

/*  Types of Data:
	- Code (00)
	- EOF (01)
	- Abdsoulte Address (04)
*/

#define HEXP_RECORD_ADDRESS			0x08000000
#define HEXP_STARTING_DELIMITER		':'
#define HEXP_ENDING_DELIMITER		'\n'

typedef enum
{
	HEXP_Code = 0x00,
	HEXP_EOF = 0x01,
	HEXP_ABSADD = 0x04,
}HEXP_DataType_t;

typedef struct
{
	u16 byte_count;
	u16 record_type;
	u16 data[8];
	u32 address;
}hexRecord_t;

void HEXP_Get_Data(u8* Copy_u8HexRecord/*takes one hex record*/, u16* Copy_u16Data/*return Data*/);

void HEXP_Get_RecordData(u8 volatile Copy_u8HexRecord[]/*takes one hex record*/, hexRecord_t* Copy_u16RecordData/*return Data*/);


#endif /* SERVICES_HEX_PARSER_HEX_PARSER_H_ */
