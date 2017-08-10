/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef TTY_H
#define TTY_H

#include <stdio.h>
#include <stdint.h>

int terminal_initialize();
int terminal_setcolor(uint8_t color);
int terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y);
int terminal_putchar(char c);
int terminal_write(const char* data, size_t size);
int terminal_writestring(const char* data);
size_t strlen(const char* str);
#endif