#include "scoreboard.h"

void displayScores(char scores[4]){
	ascii_clear_screen();
	if(scores[0] != -1){
		ascii_gotoxy(1,1);
		ascii_write_word(getPlayerName(0));
		ascii_write_word(":  ");
		ascii_write_number(scores[0]);
	}
	if(scores[1] != -1){
		ascii_gotoxy(11,1);
		ascii_write_word(getPlayerName(1));
		ascii_write_word(": ");
		ascii_write_number(scores[1]);
	}
	if(scores[2] != -1){
		ascii_gotoxy(1,2);
		ascii_write_word(getPlayerName(2));
		ascii_write_word(": ");
		ascii_write_number(scores[2]);
	}
	if(scores[3] != -1){
		ascii_gotoxy(11,2);
		ascii_write_word(getPlayerName(3));
		ascii_write_word(":  ");
		ascii_write_number(scores[3]);
	}
}

void displayWinner(char player, char points){
	ascii_clear_screen();
	ascii_gotoxy(1,1);
	ascii_write_word("A WINNER IS YOU!!!");
	ascii_gotoxy(1,2);
	ascii_write_word(getPlayerName(player));
	ascii_gotoxy(13,2);
	ascii_write_number(points);
	ascii_write_word(" pts");
}

void displayWelcome(void){
	ascii_clear_screen();
	ascii_gotoxy(2,1);
	ascii_write_word("ACHTUNG DIE KURVE!");
	ascii_gotoxy(7,2);
	ascii_write_word("Press A!");
}

char* getPlayerName(char player)
{
	switch(player)
	{
		case 0:
			return "Red";
		case 1:
			return "Green";
		case 2:
			return "Pink";
		case 3:
			return "Blue";
	}
	return "Unknown";
}