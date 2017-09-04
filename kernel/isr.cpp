/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "panic.h"
#include "isr.h"
#include "graphics.h"
#include <stdio.h>
#include <stdint.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)            
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define KERNEL_CS 0x08
typedef struct {
    uint16_t low_offset;
    uint16_t sel; 
    uint8_t always0;
    uint8_t flags; 
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t ;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

static void set_idt_gate(int n, uint32_t handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = high_16(handler);
}


void isr_install() {
    set_idt_gate(0, (uint32_t)isr0);
    set_idt_gate(1, (uint32_t)isr1);
    set_idt_gate(2, (uint32_t)isr2);
    set_idt_gate(3, (uint32_t)isr3);
    set_idt_gate(4, (uint32_t)isr4);
    set_idt_gate(5, (uint32_t)isr5);
    set_idt_gate(6, (uint32_t)isr6);
    set_idt_gate(7, (uint32_t)isr7);
    set_idt_gate(8, (uint32_t)isr8);
    set_idt_gate(9, (uint32_t)isr9);
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    set_idt_gate(12, (uint32_t)isr12);
    set_idt_gate(13, (uint32_t)isr13);
    set_idt_gate(14, (uint32_t)isr14);
    set_idt_gate(15, (uint32_t)isr15);
    set_idt_gate(16, (uint32_t)isr16);
    set_idt_gate(17, (uint32_t)isr17);
    set_idt_gate(18, (uint32_t)isr18);
    set_idt_gate(19, (uint32_t)isr19);
    set_idt_gate(20, (uint32_t)isr20);
    set_idt_gate(21, (uint32_t)isr21);
    set_idt_gate(22, (uint32_t)isr22);
    set_idt_gate(23, (uint32_t)isr23);
    set_idt_gate(24, (uint32_t)isr24);
    set_idt_gate(25, (uint32_t)isr25);
    set_idt_gate(26, (uint32_t)isr26);
    set_idt_gate(27, (uint32_t)isr27);
    set_idt_gate(28, (uint32_t)isr28);
    set_idt_gate(29, (uint32_t)isr29);
    set_idt_gate(30, (uint32_t)isr30);
    set_idt_gate(31, (uint32_t)isr31);

    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}

/*Handlers*/
void isr0()
{
    printk("[PANIC: Exception] Division by Zero /n");
    panic();    
}
void isr1()
{
    printk("[PANIC: Exception] Debug /n");    
    panic();
}
void isr2()
{
    printk("[PANIC: Exception] Non maskable interput");    
    panic();
}
void isr3()
{
    printk("[PANIC: Exception] Breakpoint");    
    panic();
}
void isr4()
{
    printk("[PANIC: Exception] Info detected overflow");
    panic();
}
void isr5()
{
    printk("[PANIC: Exception] Out of Bounds");    
    panic();
}
void isr6()
{
    printk("[PANIC: Exception] Invalid Opcode");    
    panic();
}
void isr7()
{
    printk("[PANIC: Exception] No Coprocessor");    
    panic();
}
void isr8()
{
    printk("[PANIC: Exception] Double Fault");    
    panic();
}
void isr9()
{
    printk("[PANIC: Exception] Coprocessor Segment Overrun");    
    panic();
}
void isr10()
{
    printk("[PANIC: Exception] Bad TSS");    
    panic();
}
void isr11()
{
    printk("[PANIC: Exception] Segment Not Present");    
    panic();
}
void isr12()
{
    printk("[PANIC: Exception] Stack Fault");    
    panic();
}
void isr13()
{
    printk("[PANIC: Exception] General Protection Fault");    
    panic();
}
void isr14()
{
    printk("[PANIC: Exception] Page Fault");    
    panic();
}
void isr15()
{
    printk("[PANIC: Exception] Unknown Interrupt");    
    panic();
}
void isr16()
{
    printk("[PANIC: Exception] Coprocessor Fault");    
    panic();
}
void isr17()
{
    printk("[PANIC: Exception] Alignment Check");    
    panic();
}
void isr18()
{
    printk("[PANIC: Exception] Machine Check");    
    panic();
}
void isr19()
{
    printk("[PANIC: Exception] Reserved");    
    panic();
}
void isr20()
{
    printk("[PANIC: Exception] Reserved");     
    panic();
}
void isr21()
{
    printk("[PANIC: Exception] Reserved");     

    panic();
}
void isr22()
{
    printk("[PANIC: Exception] Reserved");     
  
    panic();
}
void isr23()
{
    printk("[PANIC: Exception] Reserved");     
   
    panic();
}
void isr24()
{
    printk("[PANIC: Exception] Reserved");     

    panic();
}
void isr25()
{
    printk("[PANIC: Exception] Reserved");     

    panic();
}
void isr26()
{
    printk("[PANIC: Exception] Reserved");     

    panic();
}
void isr27()
{
    printk("[PANIC: Exception] Reserved");     

    panic();
}
void isr28()
{
    printk("[PANIC: Exception] Reserved");     
   
    panic();
}
void isr29()
{
    printk("[PANIC: Exception] Reserved");     

    panic();
}
void isr30()
{
    printk("[PANIC: Exception] Reserved");     
    
    panic();
}
void isr31()
{
    printk("[PANIC: Exception] Reserved");     
    
    panic();
}


/*End Handlers*/

