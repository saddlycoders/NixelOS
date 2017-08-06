/*
  The NixelOS main c++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdint.h>
#include "kernel.h"
extern "C" int kmain()
{
	
	
	/* End of Kernel */
    stop();
	return 0;
}

int stop()
{
    while(1);
	return 0;	
}