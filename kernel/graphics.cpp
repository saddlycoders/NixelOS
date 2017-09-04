/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
  F18GE - Felix18 Graphics Engine
*/

#include "graphics.h"
#include "../stdint/string.h"
#include "memory.h"
#include "tty.h"
#include <stdio.h>
#include <stdint.h>


int printk(const char* format)
{
	terminal_write(format, strlen(format));	
	return 0;
}
