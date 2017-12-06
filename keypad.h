#ifndef KEYPAD_H
#define KEYPAD_H

#include "gpio.h"

unsigned char keyb(void);
void activateRow(unsigned char r);
unsigned char readColumn(void);
void keypad_init(void);

#endif