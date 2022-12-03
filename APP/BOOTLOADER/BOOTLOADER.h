#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

/*
 *=======================================================================
 *						User type definitions (structures)
 *=======================================================================
 *
*/
typedef enum{
	Waiting,	/* Waiting for either a timeout or recieving a hex line through UART */
	Burning,	/* In this state the bootloader is writing application to flash as it's recieved line by line through UART*/
	Finished	/* In this state the bootloader has finished and ready to jump to application */
}enuBTL_State;
//=======================================================================




/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/
void BTL_vStart(void);

void BTL_vSetup(void);


enuBTL_State BTL_enuWaitingState(void);
enuBTL_State BTL_enuBurningState(void);
void		 BTL_enuFinishedState(void);
//=======================================================================



#endif /* BOOTLOADER_H_ */

