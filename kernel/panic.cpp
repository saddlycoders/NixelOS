/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "panic.h"
#include "graphics.h"
#include <stdio.h>
#include <stdint.h>


int panic()
{
	/* Show message */
	
	printl("Kernel Panic: abort()",0x4,true);
	
	/* Show registers */
	
	
	/* Halting */
    asm("cli"); asm("hlt");
	
	/* Fix warning */
	return 0;
}

