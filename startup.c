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
	//keypad_init();
	//graphic_init();
	ascii_init();
	
	//displayWinner("Philip", 211);
	//displayWelcome();
	char scores[] = {10,50,20,10};
	displayScores(scores);
	
	while(1)
	{
		//maybe show a welcome screen or something
		//if not running yet, start session
		if(update() == true)
		{
			//update scores
			//if session is done:
			//		winner winner chicken dinner
			//		delay for a bit?
			//		start new session probably
			//else:
			//		delay for a bit
			//		start new round
		}
		//update graphics (draw_pixels)
		delay_milli(10);
	}
}

