/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef GDT_H
#define GDT_H

#include <stdio.h>
#include <stdint.h>

void create_descriptor(uint32_t base, uint32_t limit, uint16_t flag);
int init_gdt();

#endif