/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef ATA_H
#define ATA_H

#include <stdint.h>

unsigned char ide_read(unsigned char channel, unsigned char reg);
void ide_write(unsigned char channel, unsigned char reg, unsigned char data);
unsigned char ide_polling(unsigned char channel, unsigned int advanced_check);
unsigned char ide_print_error(unsigned int drive, unsigned char err);
void ide_initialize(unsigned int BAR0, unsigned int BAR1, unsigned int BAR2, unsigned int BAR3, unsigned int BAR4);
#endif