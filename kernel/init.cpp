/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdint.h>
#include "init.h"
#include "memory.h"
#include "graphics.h"
#include "gdt.h"
#include "panic.h"
#include "isr.h"

// This function initialising main modules
int modules_init()
{
	//initialize GDT descriptors
	printk("[ INFO] Initialising GDT descriptors \n");
	install_gdt();
	
	//install GDT
	printk("[ INFO] Installing GDT \n");
	loadGDT();
	
	//install ISR
	printk("[ INFO] Installing ISR \n");
	isr_install();
	
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
		

	printk("[ INFO] Initialisation completed\n");	
    return 0;	//return
}