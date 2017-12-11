#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "ascii.h"

void displayScores(signed char* scores);
void displayWinner(char player, char points);
void displayWelcome(void);
void displaySelectNPlayers(void);
char* getPlayerName(char player);


#endif