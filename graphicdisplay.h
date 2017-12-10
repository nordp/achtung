#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "gpio.h"
#include "delay.h"

typedef unsigned char uint8_t;

void graphic_ctrl_bit_set( uint8_t x );
void graphic_ctrl_bit_clear( uint8_t x );
void select_controller( uint8_t controller );
void graphic_wait_ready(void);
uint8_t graphic_read( uint8_t controller);
uint8_t graphic_read_data(uint8_t controller);
void graphic_write(uint8_t value, uint8_t controller);
void graphic_write_command(uint8_t cmd, uint8_t controller);
void graphic_write_data(uint8_t data, uint8_t controller);
void graphic_clear_screen(void);
void draw_pixels(int pixels[64][4]);
void pixel(uint8_t x, uint8_t y, uint8_t set);
void graphic_init(void);

#endif