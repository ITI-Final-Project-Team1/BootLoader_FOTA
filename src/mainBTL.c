
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "FPEC_interface.h"


#define state(_statFUN_) 	BTL_enu##_statFUN_State()

void BTL_vStart(void);
void BTL_vStart(void)
{
	while(1)
	{
		switch(currentBTLState)
		{
			case Waiting : currentBTLState = state(Waiting);  break;
			case Burning : currentBTLState = state(Burning);  break;
			case Finished: currentBTLState = state(Finished); break;
		}
	}
}


int mainBTL(void);
{
	BTL_vSetup();
	BTL_vStart();
	
	return 0;
}
