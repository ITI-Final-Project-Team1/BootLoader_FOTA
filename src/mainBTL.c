#include "../ARM_COTS/LIB/STD_TYPES.h"
#include "../ARM_COTS/LIB/BIT_MATH.h"
#include "../APP/BOOTLOADER/BOOTLOADER.h"


int mainBTL(void)
{
	BTL_vSetup();
	BTL_vStart();
	
	return 0;
}
