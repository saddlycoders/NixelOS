/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
  VFS - Virtual File System for NixelOS
*/

#include "VFS.h"
#include <stdint.h>
#include "../memory.h"
#include "initrd.h"

initrd_header_t *initrd_header;     // Заголовок.
initrd_file_header_t *file_headers; // Список заголовков файлов.
fs_node_t *initrd_root;             // Нод нашего корневого директория.
fs_node_t *initrd_dev;              // Мы также добавляем нод директория для /dev, так что мы 
                                    //сможем смонтировать в нем файловую систему devfs.
fs_node_t *root_nodes;              // Список нодов файлов.
int nroot_nodes;                    // Количество нодов файлов.

struct dirent dirent; 

static uint32_t initrd_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
   initrd_file_header_t header = file_headers[node->inode];
   if (offset > header.length)
       return 0;
   if (offset+size > header.length)
       size = header.length-offset;
   //memcpy(buffer, (uint8_t*) (header.offset+offset), size);
   return size;
} 
/*
static struct dirent *initrd_readdir(fs_node_t *node, uint32_t index)
{
   if (node == initrd_root && index == 0)
   {
     //strcpy(dirent.name, "dev");
     dirent.name[3] = 0; // Удостоверьтесь, что строка завершается символом NULL.
     dirent.ino = 0;
     return &dirent;
   }

   if (index-1 >= nroot_nodes)
       return 0;
   strcpy(dirent.name, root_nodes[index-1].name);
   dirent.name[strlen(root_nodes[index-1].name)] = 0; // Удостоверьтесь, что строка завершается символом NULL.
   dirent.ino = root_nodes[index-1].inode;
   return &dirent;
}

static fs_node_t *initrd_finddir(fs_node_t *node, char *name)
{
   if (node == initrd_root &&
       !strcmp(name, "dev") )
       return initrd_dev;

   int i;
   for (i = 0; i < nroot_nodes; i++)
       if (!strcmp(name, root_nodes[i].name))
           return &root_nodes[i];
   return 0;
} 
*/

fs_node_t *initialise_initrd(uint32_t location)
{
   // Инициализирует указатели main и заголовке файлов и заполняет корневой директорий.
   initrd_header = (initrd_header_t *)location;
   file_headers = (initrd_file_header_t *) (location+sizeof(initrd_header_t)); 
   
   // Инициализация корневого директория.
   initrd_root = (fs_node_t*)kmalloc(sizeof(fs_node_t));
   //strcpy(initrd_root->name, "initrd");
   initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->length = 0;
   initrd_root->flags = FS_DIRECTORY;
   initrd_root->read = 0;
   initrd_root->write = 0;
   initrd_root->open = 0;
   initrd_root->close = 0;
   //initrd_root->readdir = &initrd_readdir;
   //initrd_root->finddir = &initrd_finddir;
   initrd_root->ptr = 0;
   initrd_root->impl = 0; 
   
   // Инициализируем директрий /dev (требуется!)
   initrd_dev = (fs_node_t*)kmalloc(sizeof(fs_node_t));
   //strcpy(initrd_dev->name, "dev");
   initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
   initrd_dev->flags = FS_DIRECTORY;
   initrd_dev->read = 0;
   initrd_dev->write = 0;
   initrd_dev->open = 0;
   initrd_dev->close = 0;
   //initrd_dev->readdir = &initrd_readdir;
   //initrd_dev->finddir = &initrd_finddir;
   initrd_dev->ptr = 0;
   initrd_dev->impl = 0; 
   
   root_nodes = (fs_node_t*)kmalloc(sizeof(fs_node_t) * initrd_header->nfiles);
   nroot_nodes = initrd_header->nfiles; 
   
    // Для каждого файла...
   int i;
   for (i = 0; i < initrd_header->nfiles; i++)
   {
       // Отредактируем заголовок файла — в настоящее время в нем указывается смещение файла
       // относительно ramdisk. Мы хотим, чтобы оно указывалось относительно начала 
       // памяти.
       file_headers[i].offset += location;
       // Создаем нод нового файла.
       //strcpy(root_nodes[i].name, &file_headers[i].name);
       root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
       root_nodes[i].length = file_headers[i].length;
       root_nodes[i].inode = i;
       root_nodes[i].flags = FS_FILE;
       //root_nodes[i].read = &initrd_read;
       root_nodes[i].write = 0;
       root_nodes[i].readdir = 0;
       root_nodes[i].finddir = 0;
       root_nodes[i].open = 0;
       root_nodes[i].close = 0;
       root_nodes[i].impl = 0;
   }
      return initrd_root;
} 