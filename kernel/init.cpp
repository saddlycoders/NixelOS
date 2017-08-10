/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdint.h>
#include "init.h"
#include "memory.h"
#include "graphics.h"
#include "panic.h"
#include "gdt.h"

// This function initialising main modules
int modules_init()
{

	//init GDT (Global Descriptor Table)		
	printl("[init]Installing GDT",0x7,true);
	init_gdt();
	
	//Getting CMOS Memory
	int memoryAvalible = getCMOSMemory();
	if (memoryAvalible < 50000)
	{
		printl("[init]To run the Operating System, you must have at least 50 MB of RAM",0x7,true);
		panic();
	}
	else
	{
	    printl("[init]RAM is suitable for work",0x7,true);	
	}
    return 0;	
}