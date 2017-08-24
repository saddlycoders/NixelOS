/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
  Input/Output library
  
*/
#ifndef IOLIB_H
#define IOLIB_H

#include <stdio.h>
#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);


#endif