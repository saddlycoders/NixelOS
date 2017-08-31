/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

#include <stdio.h>
#include <stdint.h>
void init_descriptor_tables();

// Структура, описывающая шлюз прерываний.
struct idt_entry_struct
{
   uint16_t base_lo;             // Младшие 16 битов адреса, куда происходи переход в случае возникновения прерывания.
   uint16_t sel;                 // Переключатель сегмента ядра.
   uint8_t  always0;             // Это значение всегда должно быть нулевым.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_hi;             // Старшие 16 битов адреса, куда происходи переход.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// Структура, описывающая указатель на массив обработчиков прерываний.
// Этот формат подходит для загрузки с помощью 'lidt'.
struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t base;                // Адрес первого элемента нашего массива idt_entry_t.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

// Эти внешние директивы позволят нам получить доступ к адресам наших ассемблерных обработчиков прерываний ISR.
/*extern void isr0();
extern void isr1();
extern void isr31(); 
*/
#endif