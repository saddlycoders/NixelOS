/*
  NixelOS Kernel
  
  module name: idt.c
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "tty.h"

#include "idt.h"
/*
typedef struct {
	uint16_t address_0_15;
	uint16_t selector;
	uint8_t reserved;
	uint8_t type;
	uint16_t address_16_31;
} __attribute__((packed)) IntDesc;

typedef struct {
	uint16_t limit;
	void *base;
} __attribute__((packed)) IDTR;

IntDesc *idt = (void*)0xFFFFC000;

void set_int_handler(uint8_t index, void *handler, uint8_t type) {
	asm("pushf \n cli");
	idt[index].selector = 8;
	idt[index].address_0_15 = (size_t)handler & 0xFFFF;
	idt[index].address_16_31 = (size_t)handler >> 16;
	idt[index].type = type;
	idt[index].reserved = 0;
	asm("popf"); 
}

void init_interrupts() {
	*((size_t*)0xFFFFEFF0) = 0x8000 | 3;
	//memset(idt, 0, 256 * sizeof(IntDesc));
    //IDTR = {256 * sizeof(IntDesc), idt};
	//asm("lidt (,%0,)"::"a"(&idtr)); 
	irq_base = 0x20;
	irq_count = 16;
	outportb(0x20, 0x11);
	outportb(0x21, irq_base);
	outportb(0x21, 4);
	outportb(0x21, 1);
	outportb(0xA0, 0x11);
	outportb(0xA1, irq_base + 8);
	outportb(0xA1, 2);
	outportb(0xA1, 1);
	//set_int_handler(irq_base, timer_int_handler, 0x8E);
	asm("sti");
} 
*/