/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdint.h>
#include "init.h"
#include "memory.h"
#include "graphics.h"
#include "gdt.h"

// This function initialising main modules
int modules_init()
{
	//init GDT (Global Descriptor Table)
	init_gdt();
	
	//Getting CMOS Memory
	getCMOSMemory();
    return 0;	
}