#ifndef DELAY_H
#define DELAY_H

#define STK_CTRL	((volatile unsigned int *)(0xE000E010))
#define STK_LOAD	((volatile unsigned int *)(0xE000E014))
#define STK_VAL		((volatile unsigned int *)(0xE000E018))

void delay_250ns( void );
void delay_500ns( void );
void delay_micro(unsigned int us);
void delay_milli( unsigned int ms );

#endif