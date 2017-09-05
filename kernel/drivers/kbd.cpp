/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "kbd.h"
#include "libc++/io.h"
#include "graphics.h"
#include <stdio.h>
#include <stdint.h>

int readStr()
{

    int *buffstr;
    uint8_t i = 0;
    uint8_t reading = 1;
    while(reading)
    {
        if(inb(0x64) & 0x1)                 
        {
            switch(inb(0x60))
            { 
      /*case 1:
                printk("(char)27);           Escape button
                buffstr  = (char)27;
                i++;
                break;*/
        case 2:
                printk("1");
                buffstr[i] = '1';
                i++;
                break;
        case 3:
                printk("2");
                buffstr[i] = '2';
                i++;
                break;
        case 4:
                printk("3");
                buffstr[i] = '3';
                i++;
                break;
        case 5:
                printk("4");
                buffstr[i] = '4';
                i++;
                break;
        case 6:
                printk("5");
                buffstr[i] = '5';
                i++;
                break;
        case 7:
                printk("6");
                buffstr[i] = '6';
                i++;
                break;
        case 8:
                printk("7");
                buffstr[i] = '7';
                i++;
                break;
        case 9:
                printk("8");
                buffstr[i] = '8';
                i++;
                break;
        case 10:
                printk("9");
                buffstr[i] = '9';
                i++;
                break;
        case 11:
                printk("0");
                buffstr[i] = '0';
                i++;
                break;
	    case 12:
                printk("-");
                buffstr[i] = '-';
                i++;
                break;
				
		case 13:
                printk("=");
                buffstr[i] = '=';
                i++;
                break;
	    case 14:
                printk("/");
                buffstr[i] = '/';
                i++;
                break;
        case 16:
                printk("q");
                buffstr[i] = 'q';
                i++;
                break;
        case 17:
                printk("w");
                buffstr[i] = 'w';
                i++;
                break;
        case 18:
                printk("e");
                buffstr[i] = 'e';
                i++;
                break;
        case 19:
                printk("r");
                buffstr[i] = 'r';
                i++;
                break;
        case 20:
                printk("t");
                buffstr[i] = 't';
                i++;
                break;
        case 21:
                printk("y");
                buffstr[i] = 'y';
                i++;
                break;
        case 22:
                printk("u");
                buffstr[i] = 'u';
                i++;
                break;
        case 23:
                printk("i");
                buffstr[i] = 'i';
                i++;
                break;
        case 24:
                printk("o");
                buffstr[i] = 'o';
                i++;
                break;
        case 25:
                printk("p");
                buffstr[i] = 'p';
                i++;
                break;
        case 26:
                printk("[");
                buffstr[i] = '[';
                i++;
                break;
        case 27:
                printk("]");
                buffstr[i] = ']';
                i++;
                break;
        case 28:                           //Enter key
               // printch('\n');
               // buffstr[i] = '\n';
                  i++;
               reading = 0;
                break;			
		case 29:                           //Left CTRL
               // printch('\n');
               // buffstr[i] = '\n';
                  i++;
				  break;
        case 30:
                printk("a");
                buffstr[i] = 'a';
                i++;
                break;
	    case 31:
                printk("s");
                buffstr[i] = 's';
                i++;
                break;
        case 32:
                printk("d");
                buffstr[i] = 'd';
                i++;
                break;
        case 33:
                printk("f");
                buffstr[i] = 'f';
                i++;
                break;
        case 34:
                printk("g");
                buffstr[i] = 'g';
                i++;
                break;			
        case 35:
                printk("h");
                break;			
        case 36:
                printk("j");
                break;				
        case 37:
                printk("k");
                break;
	    case 38:
                printk("l");
                break;
	    case 39:
                printk(";");
                break;

            }
        }
    }           

}

