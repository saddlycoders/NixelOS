/*
  NixelOS Kernel
  
  module name: logs.c
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "logs.h"





void write_log(const char *def)
{
	logs[lognum++]=def;
}

