#include "delay.h"

void delay_250ns( void )
{
	/* SystemCoreClock = 168000000 */
	*STK_CTRL = 0;
	*STK_LOAD = ((168 / 4) - 1);
	*STK_VAL = 0;
	*STK_CTRL = 5;
	while((*STK_CTRL & 0x10000) == 0)
	{
	}
	*STK_CTRL = 0;
}

void delay_500ns( void )
{
	/* SystemCoreClock = 168000000 */
	*STK_CTRL = 0;
	*STK_LOAD = ((168 / 2) - 1);
	*STK_VAL = 0;
	*STK_CTRL = 5;
	while((*STK_CTRL & 0x10000) == 0)
	{
	}
	*STK_CTRL = 0;
}

void delay_micro(unsigned int us)
{
	while(us--)
	{
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay_250ns();
	}
} 

void delay_milli( unsigned int ms )
{
	#ifdef SIMULATOR
		ms /= 1000;
		ms++;
	#endif
	int i;
	while( ms-- )
	{
		for( i = 0; i < 1000; i++ )
		{
			delay_250ns();
			delay_250ns();
			delay_250ns();
			delay_250ns();
		}
	}
}