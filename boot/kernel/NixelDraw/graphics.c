/*
  NixelOS Kernel
  
  module name: graphics.c
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "graphics.h"


/* Рисование Пикселя */
void putpixel(unsigned char* screen, int x,int y, int color) {
    unsigned where = x*4 + y*3200;
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}

/* Очистка Экрана  80x25 */
void clear_scr()
{
	char *vidptr = (char*)0xb8000; 	
	unsigned int i = 0;
	unsigned int j = 0;


	while(j < 80 * 25 * 2) {

		vidptr[j] = ' ';

		vidptr[j+1] = 0x07; 		
		j = j + 2;
	}

	j = 0;
}
/* Печать строки */
void print(char* message, int color)
{
	terminal_setcolor(color);
	terminal_writestring(message);
}
/* Печать на новой строке */
void printf(char* message, int color)
{
	terminal_setcolor(color);
	terminal_writestringf(message);
}
