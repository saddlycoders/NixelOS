/*
  NixelOS Kernel
  
  module name: print.c
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include "print.h"


void print(char* message, int color)
{
	terminal_setcolor(color);
	terminal_writestring(message);
}

void printf(char* message, int color)
{
	terminal_setcolor(color);
	terminal_writestringf(message);
}

