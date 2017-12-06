#include "graphicdisplay.h"

void graphic_ctrl_bit_set( uint8_t x )
{
	uint8_t c;
	c = *GPIO_LCD_ODR_LOW;
	c &= ~B_SELECT;
	c |= (~B_SELECT & x);
	*GPIO_LCD_ODR_LOW = c;
}

void graphic_ctrl_bit_clear( uint8_t x )
{
	uint8_t c;
	c = *GPIO_LCD_ODR_LOW;
	c &= ~B_SELECT;
	c &= ~x;
	*GPIO_LCD_ODR_LOW = c;
}

void select_controller( uint8_t controller )
{
	switch(controller)
	{
		case 0:
			graphic_ctrl_bit_clear(B_CS1|B_CS2);
			break;
		case B_CS1:
			graphic_ctrl_bit_set(B_CS1);
			graphic_ctrl_bit_clear(B_CS2);
			break;
		case B_CS2:
			graphic_ctrl_bit_set(B_CS2);
			graphic_ctrl_bit_clear(B_CS1);
			break;
		case (B_CS1|B_CS2):
			graphic_ctrl_bit_set(B_CS1|B_CS2);
			break;
	}
}

void graphic_wait_ready(void) {
	uint8_t c;
	graphic_ctrl_bit_clear(B_E);
	*GPIO_LCD_MODER = 0x00005555; // 15-8 inputs, 7-0 outputs
	graphic_ctrl_bit_clear(B_RS);
	graphic_ctrl_bit_set(B_RW);
	delay_500ns();
	while(1) {
		graphic_ctrl_bit_set(B_E);
		delay_500ns();
		c = *GPIO_LCD_IDR_LOW & LCD_BUSY; //CHANGE TO HIGH IF IT DOESN'T WORK :-)
		graphic_ctrl_bit_clear(B_E);
		delay_500ns();
		if( c == 0 ) break;
	}
	*GPIO_LCD_MODER = 0x55555555; // 15-0 outputs
}

uint8_t graphic_read( uint8_t controller)
{
	graphic_ctrl_bit_clear(B_E);
	*GPIO_LCD_MODER = 0x00005555;
	graphic_ctrl_bit_set(B_RS|B_RW);
	select_controller(controller);
	delay_500ns();
	graphic_ctrl_bit_set(B_E);
	delay_500ns();
	uint8_t rv = *GPIO_LCD_IDR_HIGH;
	graphic_ctrl_bit_clear(B_E);
	*GPIO_LCD_MODER = 0x55555555;
	if(controller == B_CS1){
		select_controller(B_CS1);
		graphic_wait_ready();
	}
	if(controller == B_CS2){
		select_controller(B_CS2);
		graphic_wait_ready();
	}
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
	
	if(controller && B_CS1){
		select_controller(B_CS1);
		graphic_wait_ready();
	}
	if(controller && B_CS2){
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
	for(int page = 0 ; page < 8 ; page++ )
	{
		graphic_write_command(LCD_SET_PAGE | page, B_CS1 | B_CS2);
		graphic_write_command(LCD_SET_ADD | 0, B_CS1 | B_CS2);
		for(int add = 0 ; add < 64 ; add++ )
		{
			graphic_write_data(0, B_CS1 | B_CS2);
		}
	}
}

void pixel(uint8_t x, uint8_t y, uint8_t set)
{
	if(x > 128 || x < 1 || y > 64 || y < 1){
		return;
	}
	
	uint8_t mask = 0;
	uint8_t controller = 0;
	uint8_t x_fysisk = 0;
	uint8_t temp = 0;
	
	uint8_t index = (y - 1) / 8;
	switch((y - 1) % 8)
	{
		case 0:
			mask = 0x1;
			break;
		case 1:
			mask = 0x2;
			break;
		case 2:
			mask = 0x4;
			break;
		case 3:
			mask = 0x8;
			break;
		case 4:
			mask = 0x10;
			break;
		case 5:
			mask = 0x20;
			break;
		case 6:
			mask = 0x40;
			break;
		case 7:
			mask = 0x80;
			break;
	}
	if(set == 0){
		mask = ~mask;
	}
	
	if(x > 64){
		controller = B_CS2;
		x_fysisk = x - 65;
	}else{
		controller = B_CS1;
		x_fysisk = x - 1;
	}
	
	graphic_write_command(LCD_SET_ADD | x_fysisk, controller);
	graphic_write_command(LCD_SET_PAGE | index, controller);
	temp = graphic_read_data(controller);
	graphic_write_command(LCD_SET_ADD | x_fysisk, controller);
	if(set == 1){
		mask = mask | temp;
	}else{
		mask = mask & temp;
	}
	graphic_write_data(mask, controller);
}

void graphic_initialize(void)
{
	graphic_ctrl_bit_set(B_E);
	delay_micro(10);
	graphic_ctrl_bit_clear(B_CS1 | B_CS2 | B_RST | B_E);
	delay_milli(30);
	graphic_ctrl_bit_set(B_RST);
	graphic_write_command(LCD_OFF, B_CS1 | B_CS2);
	graphic_write_command(LCD_ON, B_CS1 | B_CS2);
	graphic_write_command(LCD_DISP_START, B_CS1 | B_CS2);
	graphic_write_command(LCD_SET_ADD, B_CS1 | B_CS2);
	graphic_write_command(LCD_SET_PAGE, B_CS1 | B_CS2);
	select_controller(0);
}

