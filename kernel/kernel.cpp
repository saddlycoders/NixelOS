/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
  
*/
#include "fs/initrd.h"
#include <stdint.h>
#include "kernel.h"
#include "panic.h"
#include "tty.h"
#include "graphics.h"
#include "init.h"
#include "nixelos.h"
#include "multiboot.h"
extern "C" int kmain(struct multiboot *mboot_ptr)
{

	/* Clean the screen and initialize terminal */
	terminal_initialize();
	SetPrintColor(0xF);
	
	// Находим местно нашего файла initial ramdisk.
   uint32_t initrd_location = *((uint32_t*)mboot_ptr->mods_addr);
   uint32_t initrd_end = *(uint32_t*)(mboot_ptr->mods_addr+4);
   
   
	/* Display the welcome text */
	printk("NixelOS kernel has started\n");
	printk("[Warning] You use an unstable version compiled on GitHub\n");
	
	/* Initialising modules */
	modules_init();

	fs_root = initialise_initrd(initrd_location);
	/* Hello message to users*/
	SetPrintColor(0xA);	
	printk("\n NixelOS Neptune Update 0.2\n ");
	printk("   + Added VFS Support\n ");
	printk("   + Added RAM DISK Support\n ");
	printk("   + Added MULTIBOOT Support\n ");
	
	/* If we are thrown out here, we cause panic */
    panic();
	
	return 0xDEADB043;
}



