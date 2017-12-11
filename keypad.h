#ifndef KEYPAD_H
#define KEYPAD_H

#include "gpio.h"

//unsigned char keyb(void);
//unsigned char readColumn(void);
void activateRow(unsigned char r);
unsigned short pollKeys(void);
void keypad_init(void);

#endif