/*
  NixelOS Kernel
  
  module name: graphics.h
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef GRAPHICS_H
#define GRAPHICS_H

void putpixel(unsigned char* screen, int x,int y, int color);
void clear_scr();
void print(char* message, int color);
void printf(char* message, int color);
#endif