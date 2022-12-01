/*****************************************************************/
/*****************************************************************/
/*************	 Author  : Abdallah Issa	    ******************/
/*************	 Layer   : MCAL					******************/
/*************	 SWC   	 : FPEC  				******************/
/*************	 Date    : 21 Nov 2022			******************/
/*************	 Version : V1.0					******************/
/*****************************************************************/
/*****************************************************************/



#ifndef MCAL_FPEC_FPEC_PRIVATE_H_
#define MCAL_FPEC_FPEC_PRIVATE_H_


#define FPEC_BASE_ADDRESS			0x40022000


#define FPEC_BASE_PAGE_ADDRESS				0x08000000
#define FPEC_ENDING_PAGE_ADDRESS 			0x0801FFFF

#define FPEC_KEY1  0x45670123
#define FPEC_KEY2  0xCDEF89AB

typedef struct
{
	volatile u32 FPEC_ACR;
	volatile u32 FPEC_KEYR;
	volatile u32 FPEC_OPTKEYR;
	volatile u32 FPEC_SR;
	volatile u32 FPEC_CR;
	volatile u32 FPEC_AR;
	volatile u32 FPEC_RESERVED;
	volatile u32 FPEC_OBR;
	volatile u32 FPEC_WRPR;
}FPEC_MemMap_t;



#define FPEC		((FPEC_MemMap_t*)FPEC_BASE_ADDRESS)

/***************************** FPEC_SR bits *****************************/

#define SR_BSY			            0
#define SR_PGERR		            2
#define SR_WRPRTERR			        4
#define SR_EOP		            	5


/***************************** FPEC_CR bits *****************************/

#define CR_PG			            0
#define CR_PER			            1
#define CR_MER			            2
#define CR_OPTPG			        4
#define CR_OPTER			        5
#define CR_STRT			            6
#define CR_LOCK			            7
#define CR_OPTWRE					9
#define CR_ERRIE					10
#define CR_EOPIE					12





#endif /* MCAL_FPEC_FPEC_PRIVATE_H_ */
