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
	printk("[ INFO] ----- Loading modules started -----\n");


	//init GDT (Global Descriptor Table)		
	printk("[ INFO] Installing GDT\n");
	init_gdt();
	
	//Get the amount of RAM through CMOS
	int memoryAvalible = getCMOSMemory();
	
	
	//Checking the minimum amount of RAM
	if (memoryAvalible < 50000) //50 MB of RAM is minimal
	{
		printk("[ INFO] To run the Operating System, you must have at least 50 MB of RAM\n");
		panic(); //Kernel panic
	}
	else
	{
	    printk("[ INFO] RAM is suitable for work\n");	
	}
	printk("[ INFO] ---- Loading modules completed -----\n");
		
	//IDE Initialising
	//ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);

	printk("[ INFO] Initialisation completed\n");	
    return 0;	//return
}