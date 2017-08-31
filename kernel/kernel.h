/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

extern "C" int kmain(struct multiboot *mboot_ptr);


#endif