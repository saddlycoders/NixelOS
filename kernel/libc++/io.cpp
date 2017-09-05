/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "io.h"
#include <stdio.h>
#include <stdint.h>

void outb(uint16_t port, uint8_t val)
{
    __asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
     __asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
} 
/*
void printf(char* str)
{
    unsigned short* VideoMemory = (unsigned short*) 0xb8000;

    for(int i=0; str[i] != '\0'; i++)
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}*/

