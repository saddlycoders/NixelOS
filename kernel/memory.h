/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdint.h>

int getCMOSMemory();

uint32_t kmalloc(uint32_t sz);
uint32_t kmalloc(uint32_t sz, int align);
uint32_t kmalloc(uint32_t sz, int align, uint32_t *phys);
#endif