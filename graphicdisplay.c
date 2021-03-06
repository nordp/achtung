#include "graphicdisplay.h"

int currentDisplay[64][4];

void graphic_ctrl_bit_set( uint8_t x )
{
	uint8_t c;
	c = *GPIO_LCD_ODR_LOW;
	c |= ( ~B_SELECT & x );
	*GPIO_LCD_ODR_LOW = c;
}

void graphic_ctrl_bit_clear( uint8_t x )
{
	uint8_t c;
	c = *GPIO_LCD_ODR_LOW;
	c = ~B_SELECT & ( c & ~x );
	*GPIO_LCD_ODR_LOW = c;
}

void select_controller( uint8_t controller )
{
	switch(controller){
		case 0:
			graphic_ctrl_bit_clear(B_CS1);
			graphic_ctrl_bit_clear(B_CS2);
			break;
		case B_CS1:
			graphic_ctrl_bit_set(B_CS1);
			graphic_ctrl_bit_clear(B_CS2);
			break;
		case B_CS2:
			graphic_ctrl_bit_clear(B_CS1);
			graphic_ctrl_bit_set(B_CS2);
			break;
		case B_CS1 | B_CS2:
			graphic_ctrl_bit_set(B_CS1 | B_CS2);
			break;
	}
}

void graphic_wait_ready(void) {
	graphic_ctrl_bit_clear(B_E);
	*GPIO_LCD_MODER = 0x00005555;
	graphic_ctrl_bit_clear(B_RS);
	graphic_ctrl_bit_set(B_RW);
	do{
		delay_500ns();
		graphic_ctrl_bit_set(B_E);
		delay_500ns();
		graphic_ctrl_bit_clear(B_E);
	} while (*GPIO_LCD_IDR_LOW & LCD_BUSY);
	delay_500ns();
	graphic_ctrl_bit_set(B_E);
	*GPIO_LCD_MODER = 0x55555555;
}

uint8_t graphic_read( uint8_t controller)
{
	graphic_ctrl_bit_clear(B_E);
	*GPIO_LCD_MODER = 0x00005555;
	graphic_ctrl_bit_set(B_RS | B_RW);
	select_controller(controller);
	delay_500ns();
	graphic_ctrl_bit_set(B_E);
	delay_500ns();
	uint8_t rv = *GPIO_LCD_IDR_HIGH;
	graphic_ctrl_bit_clear(B_E);
	*GPIO_LCD_MODER = 0x55555555;
	select_controller(controller);
	graphic_wait_ready();
	return rv;
}

uint8_t graphic_read_data(uint8_t controller)
{
	graphic_read(controller);
	return graphic_read(controller);
}

void graphic_write(uint8_t value, uint8_t controller)
{
	*GPIO_LCD_ODR_HIGH = value;
	select_controller(controller);
	delay_500ns();
	graphic_ctrl_bit_set(B_E);
	delay_500ns();
	graphic_ctrl_bit_clear(B_E);
	if (controller & B_CS1){
		select_controller(B_CS1);
		graphic_wait_ready();
	}
	if (controller & B_CS2){
		select_controller(B_CS2);
		graphic_wait_ready();
	}
	*GPIO_LCD_ODR_HIGH = 0;
	graphic_ctrl_bit_set(B_E);
	select_controller(0);
}

void graphic_write_command(uint8_t cmd, uint8_t controller)
{
	graphic_ctrl_bit_clear(B_E);
	select_controller(controller);
	graphic_ctrl_bit_clear(B_RS | B_RW);
	graphic_write(cmd, controller);
}

void graphic_write_data(uint8_t data, uint8_t controller)
{
	graphic_ctrl_bit_clear(B_E);
	select_controller(controller);
	graphic_ctrl_bit_set(B_RS);
	graphic_ctrl_bit_clear(B_RW);
	graphic_write(data, controller);
}

void graphic_clear_screen(void)
{
	for(char page = 0; page < 8; page++){
		graphic_write_command(LCD_SET_PAGE | page, B_CS1|B_CS2);
		graphic_write_command(LCD_SET_ADD | 0, B_CS1|B_CS2);
		for (char add = 0; add < 64; add++){
			graphic_write_data(0, B_CS1|B_CS2);
		}
	}
}

//Board array should be int[64][4], where 64 represents the 64 rows and 4 represents the 128 columns.
//Each int is 32 bits, so 32 columns can be represented by each int.
void draw_pixels(int pixels[64][4])
{
	for(int y = 0 ; y < 64 ; y++)
	{
		for(int x32 = 0 ; x32 < 4 ; x32++)
		{
			if(pixels[y][x32] != currentDisplay[y][x32]) //Make sure we only loop through the pixels if something has changed
			{
				for(int x = 0 ; x < 32 ; x++)
				{
					int newBit = ( (pixels[y][x32] & (1 << x )) != 0 ); //Check the bit inside the array that corresponds to the current pixel
					int oldBit = ( (currentDisplay[y][x32] & (1 << x )) != 0 ); //Do the same for the currently displayed matrix
					if(oldBit != newBit) //Make sure we only call the pixel method if this pixel has changed
					{
						pixel(x32 * 32 + x, y, newBit);
						if(newBit == 0)
							currentDisplay[y][x32] &= ~(1 << x );
						else
							currentDisplay[y][x32] |= (1 << x );
					}
				}
			
			}
		}
	}
}

void pixel(uint8_t x, uint8_t y, uint8_t set)
{
	uint8_t mask;
	if (x > 129 || y > 65) return;
	uint8_t i = (y)/8;
	switch ((y) % 8){
		case 0: mask = 1; break;
		case 1: mask = 2; break;
		case 2: mask = 4; break;
		case 3: mask = 8; break;
		case 4: mask = 0x10; break;
		case 5: mask = 0x20; break;
		case 6: mask = 0x40; break;
		case 7: mask = 0x80; break;
	}
	if (set == 0) mask = ~mask;
	
	uint8_t x_fysisk;
	uint8_t controller;
	
	if (x > 63){
		controller = B_CS2;
		x_fysisk = x-64;
	} else {
		controller = B_CS1;
		x_fysisk = x;
	}
	
	graphic_write_command(LCD_SET_ADD | x_fysisk, controller);
	graphic_write_command(LCD_SET_PAGE | i, controller);
	uint8_t temp = graphic_read_data(controller);
	graphic_write_command(LCD_SET_ADD | x_fysisk, controller);
	if (set == 1) mask = mask | temp;
	else mask = mask & temp;
	graphic_write_data(mask, controller);
}

void graphic_init(void)
{
	*GPIO_LCD_MODER = 0x55555555;
	*GPIO_LCD_OTYPER = 0xFFFF;
	*GPIO_LCD_PUPDR = 0x00000000;
	
	graphic_ctrl_bit_set(B_E);
	delay_micro(10);
	graphic_ctrl_bit_clear(B_CS1 | B_CS2 | B_RST | B_E);
	delay_milli(30);
	graphic_ctrl_bit_set(B_RST);
	graphic_write_command(LCD_OFF, B_CS1 | B_CS2);
	graphic_write_command(LCD_ON, B_CS1 | B_CS2);
	graphic_write_command(LCD_DISP_START, B_CS1 | B_CS2);
	//graphic_clear_screen();
	graphic_write_command(LCD_SET_ADD, B_CS1 | B_CS2);
	graphic_write_command(LCD_SET_PAGE, B_CS1 | B_CS2);
	select_controller(0);
	
	for(int i = 0 ; i < 64 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
		{
			currentDisplay[i][j] = 0;
		}
	}
}

