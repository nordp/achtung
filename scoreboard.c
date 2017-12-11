#include "scoreboard.h"

void displayScores(signed char* scores){
	ascii_clear_screen();
	if(*scores != -1){
		ascii_gotoxy(1,1);
		ascii_write_word(getPlayerName(0));
		ascii_write_word(":  ");
		ascii_write_number(*scores++);
	}
	if(*scores != -1){
		ascii_gotoxy(11,1);
		ascii_write_word(getPlayerName(1));
		ascii_write_word(": ");
		ascii_write_number(*scores++);
	}
	if(*scores != -1){
		ascii_gotoxy(1,2);
		ascii_write_word(getPlayerName(2));
		ascii_write_word(": ");
		ascii_write_number(*scores++);
	}
	if(*scores != -1){
		ascii_gotoxy(11,2);
		ascii_write_word(getPlayerName(3));
		ascii_write_word(":  ");
		ascii_write_number(*scores++);
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

void displaySelectNPlayers(void){
	ascii_clear_screen();
	ascii_gotoxy(2,1);
	ascii_write_word("SELECT # OF PLAYERS!");
	ascii_gotoxy(4,2);
	ascii_write_word("2-4 Players");
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