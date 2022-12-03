/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : SERVICES				******************/
/*************	 SWC   	 : HEX_PARSER			******************/
/*************	 Date    : 21 Nov 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/


#ifndef SERVICES_PARSER_ESP_PARSER_H_
#define SERVICES_PARSER_ESP_PARSER_H_



typedef struct
{
	u16 DataLength;
	u8 Data[50];
}ESPResponse_t;


void ESP_vParseData(u8* volatile Copy_pu8Response, ESPResponse_t* ExtractedData);


#endif /* SERVICES_PARSER_ESP_PARSER_H_ */
