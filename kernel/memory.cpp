/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "memory.h"
#include "libc++/io.h"
#include "graphics.h"
#include <stdio.h>
#include <stdint.h>


int getCMOSMemory()
{
    unsigned short total;
    unsigned char lowmem, highmem;
 
    outb(0x70, 0x30);
    lowmem = inb(0x71);
    outb(0x70, 0x31);
    highmem = inb(0x71);
 
    total = lowmem | highmem << 8;
    return total;
}

  uint32_t placement_address; 
uint32_t kmalloc(uint32_t sz)
{
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
} 

uint32_t kmalloc(uint32_t sz, int align)
{
  if (align == 1 && (placement_address & 0xFFFFF000)) // Если адрес еще не выровнен по границе страниц
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
} 

uint32_t kmalloc(uint32_t sz, int align, uint32_t *phys)
{
  if (align == 1 && (placement_address & 0xFFFFF000)) // Если адрес еще не выровнен по границе страниц
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  if (phys)
  {
    *phys = placement_address;
  }
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
} 
