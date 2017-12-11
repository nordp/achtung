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
	
	//displayWinner("Philip", 211);
	//char scores[] = {10,50,20,10};
	//displayScores(scores);
	
	int test[64][4];
	for(int i = 0 ; i < 64 ; i++){
		for(int j = 0 ; j < 4 ; j++){
			test[i][j] = 0;
		}
	}
	test[50][0] = 0x00000001;
	test[51][0] = 0x00000002;
	test[52][0] = 0x00000004;
	test[53][0] = 0x00000008;
	test[54][0] = 0x00000010;
	test[50][1] = 0x00000001;
	test[51][1] = 0x00000002;
	test[52][1] = 0x00000004;
	test[53][1] = 0x00000008;
	test[54][1] = 0x00000010;
	test[50][2] = 0x00000001;
	test[51][2] = 0x00000002;
	test[52][2] = 0x00000004;
	test[53][2] = 0x00000008;
	test[54][2] = 0x00000010;
	test[50][3] = 0x00000001;
	test[51][3] = 0x00000002;
	test[52][3] = 0x00000004;
	test[53][3] = 0x00000008;
	test[54][3] = 0x00000010;
	draw_pixels(test);
	while(0)
	{
		displayWelcome();
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

