#include "keypad.h"

void activateRow(unsigned char r)
{
	switch(r)
	{
		case 1: *GPIO_KEYPAD_ODR_HIGH = 0x10;
				break;
		case 2: *GPIO_KEYPAD_ODR_HIGH = 0x20;
				break;
		case 3: *GPIO_KEYPAD_ODR_HIGH = 0x40;
				break;
		case 4: *GPIO_KEYPAD_ODR_HIGH = 0x80;
				break;
		case 0: *GPIO_KEYPAD_ODR_HIGH = 0x00;
				break;
		
	}
}

unsigned char readColumn(void)
{
	unsigned char c = *GPIO_KEYPAD_IDR_HIGH;
	if( c & 0x8) return 4;
	if( c & 0x4) return 3;
	if( c & 0x2) return 2;
	if( c & 0x1) return 1;
	return 0;
}

unsigned char keyb(void)
{
	unsigned char key[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0xC,0xE,0,0xF,0xD};
	int row;
	for(row = 1 ; row <= 4 ; row++)
	{
		activateRow(row);
		char column = readColumn();
		if (column != 0)
		{
			activateRow(0);
			return key[4 * (row - 1) + (column - 1)];
		}
	}
	activateRow(0);
	return 0xFF;
}