#ifndef GAME_H
#define GAME_H

typedef enum { false, true } bool;

void startSession(unsigned int numberOfPlayers);
void startRound(void);
void setStartingPositions(int players);
void placePlayers(int players);
void placePlayer(int i);
void resetScores(int players);
void resurrectPlayers(int players);
void board_set_bit(int x, int y, int value);
int board_get_bit(int x, int y);
void board_clear(void);
void setPaused(bool newPaused);
void awardScores(int deadPlayer, int players);
char* getScores(void);
char getHighestScore(void);
char getWinner(void);
bool isRoundActive(void);
int getNumberOfAlivePlayers(int players);
int* getBoard(void);
bool update(char);

#endif