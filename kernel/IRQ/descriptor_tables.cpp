/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "descriptor_tables.h"
#include "../memory.h"
#include <stdio.h>
#include <stdint.h>

extern void idt_flush(uint32_t);
static void init_idt();
static void idt_set_gate(uint8_t,uint32_t,uint16_t,uint8_t);

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void init_descriptor_tables()
{
  init_idt();
}

static void init_idt()
{
   idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
   idt_ptr.base  = (uint32_t)&idt_entries;

   //memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

   //idt_set_gate( 0, (uint32_t)isr0 , 0x08, 0x8E);
  // idt_set_gate( 1, (uint32_t)isr1 , 0x08, 0x8E);
   
   //idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

   //idt_flush((uint32_t)&idt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   // Мы должны раскомментировать приведенную ниже операцию OR в случае, если нужен пользовательский режим.
   // Эта операция устанавливает уровень привилегий, используемый шлюзом прерываний, равным 3.
   idt_entries[num].flags   = flags /* | 0x60 */;
} 
