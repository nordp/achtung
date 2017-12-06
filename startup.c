#include "ascii.h"
#include "graphicdisplay.h"
#include "keypad.h"
#include "game.h"

void startup(void) __attribute__((naked)) __attribute__((section (".start_section")) );
void app_init(void);

void startup ( void )
{
__asm volatile(
	" LDR R0,=0x2001C000\n"		/* set stack */
	" MOV SP,R0\n"
	" BL main\n"				/* call main */
	"_exit: B .\n"				/* never return */
	) ;
}

void app_init(void)
{
	#ifdef USBDM
		*((unsigned long*) 0x40023830) = 0x18;
		__asm volatile ( " LDR R0,=0x08000209\n BLX R0 \n");
	#endif
}

void main(void)
{
	app_init();
	keypad_init();
	graphic_init();
	ascii_init();
	
	
}

