/*
  NixelOS Kernel
  
  module name: Kernel.c
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "kernel.h"

void kmain(void)
{

	//--------------------------MAIN--------------------//
	terminal_initialize();
    terminal_writestring("NixelOS Kernel loaded",0xA);	
	terminal_writestring("[Warning]You use an unstable OS version compiled on GitHub",0xE);	
	write_log('[LOG]Kernel started');
	

	while(1);
}

