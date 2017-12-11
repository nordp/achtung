#include "game.h"
#include "math.h"

bool paused;
bool unpausedOnce; //Used to clear the names from the screen on the first unpause each round.
bool roundActive;
unsigned int numPlayers;
int board[64][4]; //Matrix for the board. See graphicdisplay for explanation.

//Arrays containing values for each player, instead of creating objects. Number of players can be max 4.
char scores[4];
bool alivePlayers[4];
double positions[4][2];
double directions[4]; //In radians

#define TURN_RATE 0.5
#define SPEED 1.0
#define SCORE_PER_DEATH 5

//Start a new session with new scores
void startSession(unsigned int numberOfPlayers)
{
	numPlayers = numberOfPlayers;
	resetScores(4);
	roundActive = false;
}

//Start a new round with the same players
void startRound()
{
	roundActive = true;
	board_clear();
	setPaused(true);
	resurrectPlayers(numPlayers);
	setStartingPositions(numPlayers);
	placePlayers(numPlayers);
	//show player names
	unpausedOnce = false;
}

//Place the players at set positions, usually at the start of a round.
void setStartingPositions(int players)
{
	for(int i = 0 ; i < players ; i++){
		switch(i)
		{
			case 0:
				positions[i][0] = 5.0;
				positions[i][1] = 15.0;
				directions[i] = 0.0;
				break;
			case 1:
				positions[i][0] = 127.0 - 5.0;
				positions[i][1] = 20.0;
				directions[i] = PI;
				break;
			case 2:
				positions[i][0] = 5.0;
				positions[i][1] = 64.0 - 20.0;
				directions[i] = 0.0;
				break;
			case 3:
				positions[i][0] = 127.0 - 5.0;
				positions[i][1] = 64.0 - 15.0;
				directions[i] = PI;
				break;
		}
	}
}

//Place players at their current positions on the board
void placePlayers(int players)
{
	for(int i = 0 ; i < players ; i++)
	{
		placePlayer(i);
	}
}

void placePlayer(int i)
{
	board_set_bit((int)positions[i][0], (int)positions[i][1], 1);
}

void resetScores(int players)
{
	for(int i = 0 ; i < players ; i++)
	{
		scores[i] = 0;
	}
	for(int i = 0 ; i < (4 - players) ; i++) //Set the scores of inactive players to -1
	{
		scores[3 - i] = -1;
	}
}

void resurrectPlayers(int players)
{
	for(int i = 0 ; i < players ; i++) //Set all current players to alive
	{
		alivePlayers[i] = true;
	}
	for(int i = 0 ; i < (4 - players) ; i++) //Set all players that are not in the game to dead
	{
		alivePlayers[3 - i] = false;
	}
}

void board_set_bit(int x, int y, int value)
{
	int temp = board[y][x/32];
	if(value == 0)
		temp &= ~(1 << (x%32));
	else
		temp |= (1 << (x%32));
	board[y][x/32] = temp;
}

int board_get_bit(int x, int y)
{
	return ((board[y][x/32] & (1 << x%32)) != 0);
}

void board_clear(void)
{
	for(int i = 0 ; i < 64 ; i++) //Clear the board
	{
		for(int j = 0 ; j < 4 ; j++)
		{
			board[i][j] = 0;
		}
	}
}

void setPaused(bool newPaused)
{
	paused = newPaused;
	if(unpausedOnce == false && newPaused == false)
	{
		board_clear();
		placePlayers(numPlayers);
		unpausedOnce = true;
	}
}

void awardScores(int deadPlayer, int players)
{
	for(int i = 0 ; i < players ; i++)
	{
		if(i != deadPlayer)
			scores[i] += SCORE_PER_DEATH;
	}
}

char* getScores(void)
{
	return scores;
}

char getHighestScore(void) //Method to find the highest score
{
	char highest = 0;
	for(int i = 0 ; i < numPlayers ; i++)
	{
		if(scores[i] > highest)
			highest = scores[i];
	}
	return highest;
}

char getWinner(void) //Method to find the player with the highest score
{
	char highest = 0;
	char index = 0;
	for(int i = 0 ; i < numPlayers ; i++)
	{
		if(scores[i] > highest){
			highest = scores[i];
			index = i;
		}
	}
	return index;
}

bool isRoundActive(void)
{
	return roundActive;
}

int getNumberOfAlivePlayers(int players)
{
	int total = 0;
	for(int i = 0 ; i < players ; i++)
	{
		if(alivePlayers[i] = true)
			total += 1;
	}
}

int* getBoard(void)
{
	return board;
}

bool update(char directionControls)
{
	if(paused == false)
	{
		for(int i = 0 ; i < numPlayers ; i++)
		{
			if(alivePlayers[i] == true)
			{
				if(directionControls & (1 << (2*i)) != 0)
					directions[i] += TURN_RATE;
				else if(directionControls & (1 << (2*i + 1)) != 0)
					directions[i] -= TURN_RATE;
				
				double oldx = positions[i][0]; //Weird bug if we don't do this :-)
				double newx = oldx + cos(directions[i])*SPEED;
				double oldy = positions[i][1];
				double newy = oldy + sin(directions[i])*SPEED;
				int newxi = (int) newx;
				int newyi = (int) newy;
				if( !(newxi < 0 || newxi > 127 || newyi < 0 || newyi > 63) && board_get_bit(newxi, newyi) == 0)
				{
					positions[i][0] = newx;
					positions[i][1] = newy;
					placePlayer(i);
				}else{
					alivePlayers[i] = false;
					awardScores(i, numPlayers);
				}
			}
		}
		if(getNumberOfAlivePlayers(numPlayers) <= 1)
		{
			roundActive = false;
			return true;
		}
	}
	return false;
}