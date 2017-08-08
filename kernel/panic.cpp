/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "panic.h"
#include <stdio.h>
#include <stdint.h>


int panic(/*char* reason*/)
{
	while(1){}
	return 0;
}