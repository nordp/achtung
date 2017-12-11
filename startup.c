#include "scoreboard.h"
#include "graphicdisplay.h"
#include "controller.h"
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
{	app_init();
	keypad_init();
	graphic_init();
	ascii_init();
	
	//displayWinner("Philip", 211);
	//char scores[] = {10,50,20,10};
	//displayScores(scores);
	displayWinner("Hej", getCurrentDirections());
	
	while(!isPauseReleased()){}
	while(!isPauseReleased()){}
	while(!isPauseReleased()){}
	while(!isPauseReleased()){}
	while(!isPauseReleased()){}
	
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
	
	while(1) //Loop back to welcome screen after finishing a game session
		{
		displayWelcome();
		
		int targetScore = 0;
		while(1) //Wait for user to input number of players
		{
			char keypress = 2; //char keypress = getNumberOfPlayersInput();
			if(keypress != 0)
			{
				startSession(keypress);
				targetScore = keypress * 5; //Set the target score to number of players times five.
				break;
			}
		}
		
		displayScores(getScores());
		while(1) //Main game loop, with update calls. This is also where new rounds are started within one session.
		{
			if(isRoundActive() == false){
				startRound();
				setPaused(false); //Temporary
			}
			if(update(0) == true) //NOTE: update() is the main update method. Returns true if the game is over.
			{
				displayScores(getScores());
				unsigned char highscore = getHighestScore();
				if(highscore >= targetScore)
				{
					displayWinner(getWinner(), highscore);
					
					while(1) //Wait for user to press pause key
					{
						char pausePressed = 0; //char pausePressed = isPauseKeyReleased();
						if(pausePressed)
							break;
					}
					break; //Break the game loop and start a new session with the outer loop.
				}
			}
			draw_pixels(getBoard());
			delay_milli(10);
		}
		
	}
}

