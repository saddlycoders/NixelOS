/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "graphics.h"
#include "tty.h"
#include <stdio.h>
#include <stdint.h>

int fillrect(unsigned char *vram, unsigned char r, unsigned char g, unsigned   char b, unsigned char w, unsigned char h) {
    unsigned char *where = vram;
    int i, j;
 
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            //putpixel(vram, 64 + j, 64 + i, (r << 16) + (g << 8) + b);
            where[j*4] = r;
            where[j*4 + 1] = g;
            where[j*4 + 2] = b;
        }
        where+=3200;
    }
	return 0;
}
/* Print in screen */
int printl(const char* string,int color,bool newline)
{

	terminal_setcolor(color);
 	terminal_writestring(string);
	if (newline)
	{
		int width = 80;
		int nulls = width - strlen(string);
		for (size_t x = 0; x < nulls; x++) {
			terminal_putchar(' ');
		}
	}
	return 0;
}