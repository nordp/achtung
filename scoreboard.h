#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "ascii.h"

void displayScores(char scores[4]);
void displayWinner(char player, char points);
void displayWelcome(void);
char* getPlayerName(char player);


#endif