#include "scoreboard.h"

void displayScores(char scores[4]){
	ascii_clear_screen();
	if(scores[0]){
		ascii_gotoxy(1,1);
		ascii_write_word("Red:  ");
		ascii_write_number(scores[0]);
	}
	if(scores[1]){
		ascii_gotoxy(11,1);
		ascii_write_word("Green: ");
		ascii_write_number(scores[1]);
	}
	if(scores[2]){
		ascii_gotoxy(1,2);
		ascii_write_word("Pink: ");
		ascii_write_number(scores[2]);
	}
	if(scores[3]){
		ascii_gotoxy(11,2);
		ascii_write_word("Blue:  ");
		ascii_write_number(scores[3]);
	}
}

void displayWinner(char* name, int points){
	ascii_clear_screen();
	ascii_gotoxy(1,1);
	ascii_write_word("A WINNER IS YOU!!!");
	ascii_gotoxy(1,2);
	ascii_write_word(name);
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