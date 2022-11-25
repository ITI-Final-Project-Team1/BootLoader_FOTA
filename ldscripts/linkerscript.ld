/* linker_script
Eng.Magdy Adel
*/

MEMORY
{
FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 4k
SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20k
}



/* The '__stack' definition .*/
__stack = ORIGIN(SRAM) + LENGTH(SRAM);
_E_stack = __stack; 	/* STM specific definition */


/* 
The entry point is informative, for debuggers and simulators,
 since the Cortex-M vector points to it anyway.
ENTRY(_start)
*/

SECTIONS
{
	.text :
	{
		*(.vectors*)
		*(.text*) /* all remaining code */
		*(.rodata) 		/* read-only data (constants) */
		
		_E_text = . ; 		/* End of .text section */
	}> FLASH

	.data : 
	{
		_S_DATA = . ;		/* Start of .data section */
		*(.data*)
		. = ALIGN(4) ;		/* to make word aligned after data section */   
		_E_DATA = . ;		/* End of .data section */
	}>SRAM AT> FLASH 			/* virtual addresses exists in RAM but at loading time burn in FLASH */ 
	
	.bss :
	{
		_S_bss = . ;		/* Start of .bss section */
		*(.bss*)
		. = ALIGN(4) ;		/* to make word aligned after data section */ 
		_E_bss = . ;		/* End of .bss section */
	}> SRAM
}
