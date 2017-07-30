/*
  NixelOS Kernel
  
  module name: kbd.c
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "io.h"

#include "kbd.h"

void kbd_ack(void){
  while(!(inb(0x60)==0xfa));
}


void kbd_led_handling(int ledstatus){
  outb(0x60,0xed);
  kbd_ack();
  outb(0x60,ledstatus);
}

void kbd_wap()
{

    uint8_t i = 0;
    uint8_t reading = 1;
	char keys;
    while(reading)
    {
        if(inb(0x64) & 0x1)                 
        {
            switch(inb(0x60))
            { 
      /*case 1:
                terminal_putcharch('(char)27);           Escape button
                buffstr[i] = (char)27;
                i++;
                break;*/
        case 2:
                terminal_putchar('1');
				keys = '1';
                i++; 
                break;
		
        case 3:
                terminal_putchar('2');
				keys = '2';
                i++;
                break;
		
        case 4:
                terminal_putchar('3');
				keys = '3';
                i++;
                break;
        case 5:
                terminal_putchar('4');
				keys = '4';
                i++;
                break;
        case 6:
                terminal_putchar('5');
				keys = '5';
                i++;
                break;
        case 7:
                terminal_putchar('6');
				keys = '6';
                i++;
                break;
        case 8:
                terminal_putchar('7');
				keys = '7';
                i++;
                break;
        case 9:
                terminal_putchar('8');
				keys = '8';
                i++;
                break;
        case 10:
                terminal_putchar('9');
				keys = '9';
                i++;
                break;
        case 11:
                terminal_putchar('0');
				keys = '0';
                i++;
                break;
        case 12:
                terminal_putchar('-');
				keys = '-';
                i++;
                break;
        case 13:
                terminal_putchar('=');
				keys = '=';
                i++;
                break;
        case 14:
                terminal_putchar('/');
				keys = '/';
                i++;
                break;
       /* case 15:
                terminal_putcharch('\t');          Tab button
                break; */
        case 16:
                terminal_putchar('q');
				keys = 'q';
                i++;
                break;
        case 17:
                terminal_putchar('w');
				keys = 'w';
                i++;
                break;
        case 18:
                terminal_putchar('e');
				keys = 'e';
                i++;
                break;
        case 19:
                terminal_putchar('r');
				keys = 'r';
                i++;
                break;
        case 20:
                terminal_putchar('t');
				keys = 't';
                i++;
                break;
        case 21:
                terminal_putchar('y');
				keys = 'y';
                i++;
                break;
        case 22:
                terminal_putchar('u');
				keys = 'u';
                i++;
                break;
        case 23:
                terminal_putchar('i');
				keys = 'i';
                i++;
                break;
        case 24:
                terminal_putchar('o');
				keys = 'o';
                i++;
                break;
        case 25:
                terminal_putchar('p');
				keys = 'p';
                i++;
                break;
        case 26:
                terminal_putchar('[');
				keys = '[';
                i++;
                break;
        case 27:
                terminal_putchar(']');
				keys = ']';
                i++;
                break;
        //case 28:
               // terminal_putcharch('\n');
               // buffstr[i] = '\n';
                  //i++;
               //reading = 0;
               // break;
      /*  case 29:
                terminal_putcharch('q');           Left Control
                buffstr[i] = 'q';
                i++;
                break; */
        case 30:
                terminal_putchar('a');
				keys = 'a';
                i++;
                break;
        case 31:
                terminal_putchar('s');
				keys = 's';
                i++;
                break;
        case 32:
                terminal_putchar('d');
				keys = 'd';
                i++;
                break;
        case 33:
                terminal_putchar('f');
				keys = 'f';
                i++;
                break;
        case 34:
                terminal_putchar('g');
				keys = 'g';
                i++;
                break;
        case 35:
                terminal_putchar('h');
				keys = 'h';
                i++;
                break;
        case 36:
                terminal_putchar('j');
				keys = 'j';
                i++;
                break;
        case 37:
                terminal_putchar('k');
				keys = 'k';
                i++;
                break;
        case 38:
                terminal_putchar('l');
				keys = 'l';
                i++;
                break;
        case 39:
                terminal_putchar(';');
				keys = ';';
                i++;
                break;
        case 40:
                terminal_putchar((char)44);               //   Single quote (')
                break;
        case 41:
                terminal_putchar((char)44);               // Back tick (`)
                break;
     /* case 42:                                 Left shift 
                terminal_putcharch('q');
                buffstr[i] = 'q';
                i++;
                break; */
        case 43:                                 // (< for somekeyboards)   
                terminal_putchar((char)92);
                break;
        case 44:
                terminal_putchar('z');
				keys = 'z';
                i++;
                break;
        case 45:
                terminal_putchar('x');
				keys = 'x';
                i++;
                break;
        case 46:
                terminal_putchar('c');
				keys = 'c';
                i++;
                break;
        case 47:
                terminal_putchar('v');
				keys = 'v';
                i++;
                break;                
        case 48:
                terminal_putchar('b');
				keys = 'b';
                i++;
                break;               
        case 49:
                terminal_putchar('n');
				keys = 'n';
                i++;
                break;                
        case 50:
                terminal_putchar('m');
				keys = 'm';
                i++;
                break;               
        case 51:
                terminal_putchar(',');
				keys = ',';
                i++;
                break;                
        case 52:
                terminal_putchar('.');
				keys = '.';
                i++;
                break;            
        case 53:
                terminal_putchar('/');
				keys = '/';
                i++;
                break;            
        case 54:
                terminal_putchar('.');
				keys = '.';
                i++;
                break;            
        case 55:
                terminal_putchar('/');
				keys = '/';
                i++;
                break;            
      /*case 56:
                printch(' ');           Right shift
                buffstr[i] = ' ';
                i++;
                break; */
        case 57:
                terminal_putchar(' ');
	            break;
            }
        }
    }
	return keys;
}