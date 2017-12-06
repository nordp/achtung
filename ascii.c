#include "ascii.h"

void ascii_ctrl_bit_set( unsigned char x )
{
	unsigned char c;
	c = *GPIO_LCD_ODR_LOW;
	c |= ( B_SELECT | x );
	*GPIO_LCD_ODR_LOW = c;
}

void ascii_ctrl_bit_clear( unsigned char x )
{
	unsigned char c;
	c = *GPIO_LCD_ODR_LOW;
	c = B_SELECT | ( c & ~x );
	*GPIO_LCD_ODR_LOW = c;
}

void ascii_write_controller( unsigned char c )
{
	ascii_ctrl_bit_set( B_E );
	*GPIO_LCD_ODR_HIGH = c;
	delay_250ns();
	ascii_ctrl_bit_clear( B_E );
}

unsigned char ascii_read_controller( void )
{
	unsigned char c;
	ascii_ctrl_bit_set( B_E );
	delay_250ns(); /* max 360 ns */
	delay_250ns();
	c = *GPIO_LCD_IDR_HIGH;
	ascii_ctrl_bit_clear( B_E );
	return c;
}

void ascii_write_cmd( unsigned char command )
{
	while(ascii_read_status() & 0x80)
	{}
	ascii_ctrl_bit_clear(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(command);
}

void ascii_write_data( unsigned char data )
{
	ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(data);
}

unsigned char ascii_read_status( void )
{
	*GPIO_LCD_MODER = 0x00005555;
	ascii_ctrl_bit_clear(B_RS);
	ascii_ctrl_bit_set(B_RW);
	unsigned char rv = ascii_read_controller();
	*GPIO_LCD_MODER = 0x55555555;
	return rv;
}

unsigned char ascii_read_data( void )
{
	*GPIO_LCD_MODER = 0x00005555;
	ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_set(B_RW);
	unsigned char rv = ascii_read_controller();
	*GPIO_LCD_MODER = 0x55555555;
	return rv;
}

void ascii_gotoxy( int x, int y )
{
	int address = x - 1;
	if(y == 2)
	{
		address += 0x40;
	}
	ascii_write_cmd(0x80 | address);
}

void ascii_write_char( unsigned char c )
{
	while(ascii_read_status() & 0x80)
	{}
	delay_micro(8);
	ascii_write_data(c);
}

void ascii_init(void)
{
	*GPIO_LCD_MODER = 0x55555555;
	*GPIO_LCD_OTYPER = 0xFFFF;
	*GPIO_LCD_PUPDR = 0x00000000;
	
	ascii_write_cmd(0x00111000);
	delay_micro(39);
	ascii_write_cmd(0x00001110);
	delay_micro(39);
	ascii_write_cmd(0x00000100);
	delay_micro(39);
}
