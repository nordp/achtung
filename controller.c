#include "controller.h"

char getCurrentDirections(){
	short keys = pollKeys();
	char currentDirections = 0;
	currentDirections |= (keys >> 8) & 0xF0;
	currentDirections |= keys & 0xF;
	return currentDirections;
}

char pausedKeysState = 0;

char isPauseReleased(void){
	short keys = pollKeys();
	char pauseKeys = keys >> 4;
	if (pauseKeys < pausedKeysState){
		pausedKeysState = pauseKeys;
		return 1;
	}
	pausedKeysState = pauseKeys;
	return 0;
}

char playersSelected(void){
	short keys = pollKeys();
	switch(keys)
	{
		case(2): return 2;
		case(4): return 3;
		case(16): return 4;
		default: return 0;
	}
}