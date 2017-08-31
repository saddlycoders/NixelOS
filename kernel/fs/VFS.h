/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef VFS_H
#define VFS_H

#include <stdint.h>
#define FS_DIRECTORY '/'
#define FS_FILE 'text.txt'
typedef uint32_t (*read_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef uint32_t (*write_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent * (*readdir_type_t)(struct fs_node*,uint32_t);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name); 
struct dirent // One of these is returned by the readdir call, according to POSIX.
{
  char name[128]; // Имя файла..
  uint32_t ino;     // Номер inode. Требеся для POSIX.
}; 


typedef struct fs_node
{
   char name[128];     // Имя файла.
   uint32_t mask;        // Маска прав доступа.
   uint32_t uid;         // Пользователь, владеющий файлом.
   uint32_t gid;         // Группа, владеющая файлом.
   uint32_t flags;       // Включает тип нода. Смотрите определение #defines, приведенное выше.
   uint32_t inode;       // Зависит от устройства, позволяет файловой системе идентифицировать файлы.
   uint32_t length;      // Размер файла в байтах.
   uint32_t impl;        // Номер,б зависящий от реализации.
   read_type_t read;
   write_type_t write;
   open_type_t open;
   close_type_t close;
   readdir_type_t readdir;
   finddir_type_t finddir;
   struct fs_node *ptr; // Используется для точек монтирования и символических ссылок.
} fs_node_t; 


extern fs_node_t *fs_root; // The root of the filesystem.


// Стандартные функции чтения, записи, открытия, закрытия. Обратите внимание,
//  что у них всех используется суффикс _fs с тем, чтобы отличать от функций чтения, 
// записи, открытия и закрытия дескрипторов файлов, а не нодов файлов. 
uint32_t read_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
uint32_t write_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);/*
void open_fs(fs_node_t *node, u8int read, u8int write);
void close_fs(fs_node_t *node);*/
struct dirent *readdir_fs(fs_node_t *node, uint32_t index);
fs_node_t *finddir_fs(fs_node_t *node, char *name); 

#endif