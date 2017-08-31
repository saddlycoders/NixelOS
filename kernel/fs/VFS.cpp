/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
  VFS - Virtual File System for NixelOS
*/

#include "VFS.h"
#include <stdint.h>

#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06 //Ссылка
#define FS_MOUNTPOINT  0x08 // Файл точка монтирования


fs_node_t *fs_root = 0; // The root of the filesystem.

uint32_t read_vfs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
  // Получил ли нод обратный вызов функции чтения?
  if (node->read != 0)
    return node->read(node, offset, size, buffer);
  else
    return 0;
}

uint32_t write_vfs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
  // Получил ли нод обратный вызов функции записи?
  if (node->write != 0)
    return node->write(node, offset, size, buffer);
  else
    return 0;
}
/*
uint32_t open(fs_node_t *node)
{
  // Получил ли нод обратный вызов функции открытия?
  if (node->open != 0)
    return node->open(node);
  else
    return 0;
}

uint32_t close(fs_node_t *node)
{
  // Получил ли нод обратный вызов функции записи?
  if (node->close != 0)
    return node->close(node);
  else
    return 0;
}
*/
struct dirent *readdir_fs(fs_node_t *node, uint32_t index)
{
  // Получил ли нод обратный вызов функции чтения директории?
  if (node->readdir != 0)
    return node->readdir(node, index);
  else
    return 0;	
} 
fs_node_t *finddir_fs(fs_node_t *node, char *name)
{
  // Получил ли нод обратный вызов функции поиска директории?
  if (node->finddir != 0)
    return node->finddir(node, name);
  else
    return 0;	
}