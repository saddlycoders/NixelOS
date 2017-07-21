/*
  NixelOS Kernel
  
  module name: shell.c
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "shell.h"


void launch_shell()
{
	char* ch;
	do
	{
		print("computer@user:",0xA);
		print("~$ ",0x4);
		terminal_setcolor(15);
        ch = kbd_wap();	
		
		if(strEql(ch,"hello"))
		{
			print("hello",0xA);
		}
		else   
	    {
		    printf("Bad command");
		    print("computer@user:",0xA);
		    print("~$ ",0x4);
		    terminal_setcolor(15);
        } 
	}while (!strEql(ch,"exit"));
}

uint8_t strEql(char* ch1, char* ch2)                     
{
        uint8_t result = 1;
        uint8_t size = strlength(ch1);
        if(size != strlength(ch2)) result =0;
        else 
        {
        uint8_t i = 0;
        for(i;i<=size;i++)
        {
                if(ch1[i] != ch2[i]) result = 0;
        }
        }
        return result;
}

uint16_t strlength(char* ch)
{
        uint16_t i = 0;           //Changed counter to 0
        while(ch[i++]);  
        return i-1;               //Changed counter to i instead of i--
}