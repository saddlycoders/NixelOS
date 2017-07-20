/*
  NixelOS Kernel
  
  module name: idt.h
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef IDT_H
#define IDT_H
/*
uint8_t irq_base;
uint8_t irq_count;

#define IRQ_HANDLER(name) void name(); \
	asm(#name ": pusha \n call _" #name " \n movb $0x20, %al \n outb %al, $0x20 \n outb %al, $0xA0 \n popa \n iret"); \
	void _ ## name()
	
void init_interrupts();
void set_int_handler(uint8_t index, void *handler, uint8_t type);
*/
#endif