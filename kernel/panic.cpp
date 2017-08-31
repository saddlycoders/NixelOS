/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "panic.h"
#include "tty.h"
#include "graphics.h"
#include <stdio.h>
#include <stdint.h>


int panic()
{
	/* Show message */
	SetPrintColor(0xD);
	printk("\n Kernel Panic: abort()");
	
	/* Show registers */
	
	
	/* Halting */
    asm("cli"); asm("hlt");
	
	/* Fix warning */
	return 0;
}

