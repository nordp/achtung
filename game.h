#ifndef GAME_H
#define GAME_H

typedef enum { false, true } bool;

void startSession(numberOfPlayers);
void startRound(void);
void setPaused(bool newPaused);
int* getScores(void);
bool update(void);

#endif