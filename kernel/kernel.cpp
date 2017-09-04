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
#include "lakesh/lakesh.h"
#include "fs/VFS.h"
extern "C" int kmain(struct multiboot *mboot_ptr)
{
                    
	/* Clean the screen and initialize terminal */
	terminal_initialize();
	SetPrintColor(0xF);
 
   
   
	/* Display the welcome text */
	printk("NixelOS kernel has started\n");
	printk("[Warning] You use an unstable version compiled on GitHub\n");
	
	/* Initialising modules */
	modules_init();
	
	lakesh_init();
	
	/* If we are thrown out here, we cause panic */
    panic();
	
}



