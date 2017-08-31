/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef INITRD_H
#define INITRD_H

#include "VFS.h"

typedef struct
{
   uint32_t nfiles; // Число файлов в ramdisk.
} initrd_header_t;

typedef struct
{
   uint8_t magic;     // Магическое число для проверки ошибок.
   char name[64];  // Имя файла.
   uint32_t offset;   // Смещение в initrd, указывающее откуда начинается файл.
   uint32_t length;   // Длина файла.
} initrd_file_header_t;

// Инициализация initial ramdisk. Ему передается адрес модуля module,
// а возвращается нод созданной файловой системы.
fs_node_t *initialise_initrd(uint32_t location);

#endif