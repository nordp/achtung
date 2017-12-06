#ifndef ASCII_H
#define ASCII_H

#include "gpio.h"
#include "delay.h"

void ascii_ctrl_bit_set( unsigned char x );
void ascii_ctrl_bit_clear( unsigned char x );
void ascii_write_cmd( unsigned char command );
void ascii_write_data( unsigned char data );
unsigned char ascii_read_status( void );
unsigned char ascii_read_data( void );
void ascii_gotoxy( int x, int y );
void ascii_write_char( unsigned char c );
void ascii_init(void);

#endif