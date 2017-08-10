/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdint.h>
#include "kernel.h"
#include "panic.h"
#include "tty.h"
#include "graphics.h"
#include "init.h"
#include "nixelos.h"
extern "C" int kmain()
{
	terminal_initialize();
	
	/* Initialising modules */
	modules_init();
	
	/* End of Kernel */
    while(1){}
	return 0;
}



