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
	write_log('[System]Kernel started');
	
	terminal_initialize();
	
    printf("NixelOS kernel loaded",0xA);	
	printf("[Warning]You use an unstable OS version compiled on GitHub",0xE);

	
    launch_shell();
 
	while(1);
}

