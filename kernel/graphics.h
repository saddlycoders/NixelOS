/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdint.h>

int fillrect(unsigned char *vram, unsigned char r, unsigned char g, unsigned   char b, unsigned char w, unsigned char h);
int printl(const char* string);

#endif