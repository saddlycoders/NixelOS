/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdint.h>
#include "init.h"
#include "memory.h"
#include "graphics.h"
#include "nixelos.h"
#include "panic.h"
#include "gdt.h"

#include "fs/ATA.h"

// This function initialising main modules
int modules_init()
{
	printl("[ INFO] ----- Loading modules started -----",0xF,true);


	//init GDT (Global Descriptor Table)		
	printl("[ INFO] Installing GDT",0xF,true);
	init_gdt();
	
	//Get the amount of RAM through CMOS
	int memoryAvalible = getCMOSMemory();
	
	
	//Checking the minimum amount of RAM
	if (memoryAvalible < 50000) //50 MB of RAM is minimal
	{
		printl("[ INFO] To run the Operating System, you must have at least 50 MB of RAM",0xF,true);
		panic(); //Kernel panic
	}
	else
	{
	    printl("[ INFO] RAM is suitable for work",0xF,true);	
	}
	printl("[ INFO] ---- Loading modules completed -----",0xF,true);
		
	//IDE Initialising
	printl("[ INFO] ---- IDE initialization started -----",0xF,true);
	ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
	printl("[ INFO] ---- IDE initialization complete ----",0xF,true);
	
    return 0;	//return
}