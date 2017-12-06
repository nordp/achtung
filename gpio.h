#ifndef GPIO_H
#define GPIO_H

//Setup
#define	GPIO_E			0x40021000
#define	GPIO_D			0x40020C00

#define	GPIO_LCD		GPIO_E
#define	GPIO_KEYPAD		GPIO_D

//Display
#define	GPIO_LCD_MODER		((volatile unsigned int *) (GPIO_LCD))
#define	GPIO_LCD_OTYPER		((volatile unsigned short *) (GPIO_LCD + 0x4))
#define GPIO_LCD_SPEEDR		((volatile unsigned int *) (GPIO_LCD + 0x8))
#define	GPIO_LCD_PUPDR		((volatile unsigned int *) (GPIO_LCD + 0xC))
#define	GPIO_LCD_IDR_LOW	((volatile unsigned char *) (GPIO_LCD + 0x10))
#define	GPIO_LCD_IDR_HIGH	((volatile unsigned char *) (GPIO_LCD + 0x11))
#define	GPIO_LCD_ODR_LOW	((volatile unsigned char *) (GPIO_LCD + 0x14))
#define	GPIO_LCD_ODR_HIGH	((volatile unsigned char *) (GPIO_LCD + 0x15))

#define B_E			0x40
#define B_SELECT	0x4
#define B_RW		0x2
#define B_RS		0x1
#define B_RST		0x20
#define B_CS2		0x10
#define B_CS1		0x8

#define LCD_ON			0x3F
#define LCD_OFF			0x3E
#define LCD_SET_ADD		0x40
#define LCD_SET_PAGE	0xB8
#define LCD_DISP_START	0xC0
#define LCD_BUSY		0x80

//Keyoad
#define	GPIO_KEYPAD_MODER		((volatile unsigned int *) (GPIO_KEYPAD))
#define	GPIO_KEYPAD_OTYPER		((volatile unsigned short *) (GPIO_KEYPAD + 0x4))
#define GPIO_KEYPAD_SPEEDR		((volatile unsigned int *) (GPIO_KEYPAD + 0x8))
#define	GPIO_KEYPAD_PUPDR		((volatile unsigned int *) (GPIO_KEYPAD + 0xC))
#define	GPIO_KEYPAD_IDR_LOW		((volatile unsigned char *) (GPIO_KEYPAD + 0x10))
#define	GPIO_KEYPAD_IDR_HIGH	((volatile unsigned char *) (GPIO_KEYPAD + 0x11))
#define	GPIO_KEYPAD_ODR_LOW		((volatile unsigned char *) (GPIO_KEYPAD + 0x14))
#define	GPIO_KEYPAD_ODR_HIGH	((volatile unsigned char *) (GPIO_KEYPAD + 0x15))

#endif