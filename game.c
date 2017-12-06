#include "game.h"

unsigned int scores[4];
bool alivePlayers[4];
bool paused;
int numPlayers;

void startSession(int numberOfPlayers)
{
	numPlayers = numberOfPlayers;
	//scores = {0, 0, 0, 0}; fixa lol
	//alivePlayers = {true, true, true, true};
}

void startRound()
{
	//clear board
	//pause
	//set all players to alive
	//set new starting positions
	//reset player directions
	//show player names
	//delay 1 second (blocking if we didnt pause, not blocking if possible)
	//remove player names
	//unpause
}

void setPaused(bool newPaused)
{
	paused = newPaused;
}

int* getScores(void)
{
	return scores;
}

bool update(void)
{
	if(paused == false)
	{
		//read keypresses
		//for each player, if alive:
		//		update direction according to respective key
		//		if new position is clear:
		//				move in direction
		//		else:
		//				set alive to false
		//				award points to every alive player
		//
		//if number of alive players is one or less:
		//		return true
		//else:
		//		return false
	}
}