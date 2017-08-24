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
	
	/* Clean the screen and initialize terminal */
	terminal_initialize();
	
	/* Display the welcome text */
	printl("NixelOS kernel has started",0x2,true);
	printl("[Warning] You use an unstable version compiled on GitHub",0xF,true);
	
	/* Initialising modules */
	modules_init();
	
	
	/* If we are thrown out here, we cause panic */
    panic();
	
}



