/*
  The NixelOS Main C++ kernel
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/

#include "ATA.h"
#include "../libc++/io.h"
#include "../graphics.h"
#include <stdint.h>

#define ATA_SR_BSY     0x80    // Busy
#define ATA_SR_DRDY    0x40    // Drive ready
#define ATA_SR_DF      0x20    // Drive write fault
#define ATA_SR_DSC     0x10    // Drive seek complete
#define ATA_SR_DRQ     0x08    // Data request ready
#define ATA_SR_CORR    0x04    // Corrected data
#define ATA_SR_IDX     0x02    // Inlex
#define ATA_SR_ERR     0x01    // Error

#define ATA_ER_BBK      0x80    // Bad sector
#define ATA_ER_UNC      0x40    // Uncorrectable data
#define ATA_ER_MC       0x20    // No media
#define ATA_ER_IDNF     0x10    // ID mark not found
#define ATA_ER_MCR      0x08    // No media
#define ATA_ER_ABRT     0x04    // Command aborted
#define ATA_ER_TK0NF    0x02    // Track 0 not found
#define ATA_ER_AMNF     0x01    // No address mark

#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA          0xC8
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_WRITE_DMA         0xCA
#define ATA_CMD_WRITE_DMA_EXT     0x35
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_PACKET            0xA0
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

#define      ATAPI_CMD_READ       0xA8
#define      ATAPI_CMD_EJECT      0x1B

#define ATA_IDENT_DEVICETYPE   0
#define ATA_IDENT_CYLINDERS    2
#define ATA_IDENT_HEADS        6
#define ATA_IDENT_SECTORS      12
#define ATA_IDENT_SERIAL       20
#define ATA_IDENT_MODEL        54
#define ATA_IDENT_CAPABILITIES 98
#define ATA_IDENT_FIELDVALID   106
#define ATA_IDENT_MAX_LBA      120
#define ATA_IDENT_COMMANDSETS  164
#define ATA_IDENT_MAX_LBA_EXT  200

#define IDE_ATA        0x00
#define IDE_ATAPI      0x01
 
#define ATA_MASTER     0x00
#define ATA_SLAVE      0x01
#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07
#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B
#define ATA_REG_CONTROL    0x0C
#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D

// Channels:
#define      ATA_PRIMARY      0x00
#define      ATA_SECONDARY    0x01
 
// Directions:
#define      ATA_READ      0x00
#define      ATA_WRITE     0x01

struct IDEChannelRegisters {
   unsigned short base;  // I/O Base.
   unsigned short ctrl;  // Control Base
   unsigned short bmide; // Bus Master IDE
   unsigned char  nIEN;  // nIEN (No Interrupt);
} channels[2];

unsigned char ide_buf[2048] = {0};
unsigned static char ide_irq_invoked = 0;
unsigned static char atapi_packet[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct ide_device {
   unsigned char  Reserved;    // 0 (Empty) or 1 (This Drive really exists).
   unsigned char  Channel;     // 0 (Primary Channel) or 1 (Secondary Channel).
   unsigned char  Drive;       // 0 (Master Drive) or 1 (Slave Drive).
   unsigned short Type;        // 0: ATA, 1:ATAPI.
   unsigned short Signature;   // Drive Signature
   unsigned short Capabilities;// Features.
   unsigned int   CommandSets; // Command Sets Supported.
   unsigned int   Size;        // Size in Sectors.
   unsigned char  Model[41];   // Model in string.
} ide_devices[4];


 
unsigned char ide_read(unsigned char channel, unsigned char reg) {
   unsigned char result;
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
   if (reg < 0x08)
      result = inb(channels[channel].base + reg - 0x00);
   else if (reg < 0x0C)
      result = inb(channels[channel].base  + reg - 0x06);
   else if (reg < 0x0E)
      result = inb(channels[channel].ctrl  + reg - 0x0A);
   else if (reg < 0x16)
      result = inb(channels[channel].bmide + reg - 0x0E);
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
   return result;
}

void ide_write(unsigned char channel, unsigned char reg, unsigned char data) {
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
   if (reg < 0x08)
      outb(channels[channel].base  + reg - 0x00, data);
   else if (reg < 0x0C)
      outb(channels[channel].base  + reg - 0x06, data);
   else if (reg < 0x0E)
      outb(channels[channel].ctrl  + reg - 0x0A, data);
   else if (reg < 0x16)
      outb(channels[channel].bmide + reg - 0x0E, data);
   if (reg > 0x07 && reg < 0x0C)
      ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
}

unsigned char ide_polling(unsigned char channel, unsigned int advanced_check) {
 
   // (I) Delay 400 nanosecond for BSY to be set:
   // -------------------------------------------------
   for(int i = 0; i < 4; i++)
      ide_read(channel, ATA_REG_ALTSTATUS); // Reading the Alternate Status port wastes 100ns; loop four times.
 
   // (II) Wait for BSY to be cleared:
   // -------------------------------------------------
   while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY)
      ; // Wait for BSY to be zero.
 
   if (advanced_check) {
      unsigned char state = ide_read(channel, ATA_REG_STATUS); // Read Status Register.
 
      // (III) Check For Errors:
      // -------------------------------------------------
      if (state & ATA_SR_ERR)
         return 2; // Error.
 
      // (IV) Check If Device fault:
      // -------------------------------------------------
      if (state & ATA_SR_DF)
         return 1; // Device Fault.
 
      // (V) Check DRQ:
      // -------------------------------------------------
      // BSY = 0; DF = 0; ERR = 0 so we should check for DRQ now.
      if ((state & ATA_SR_DRQ) == 0)
         return 3; // DRQ should be set
 
   }
 
   return 0; // No Error.
 
}

unsigned char ide_print_error(unsigned int drive, unsigned char err) {
   if (err == 0)
      return err;
 
   printk("[IDE]: ");
   if (err == 1) {printk("- Device not detected \n"); err = 19;}
   else if (err == 2) {
      unsigned char st = ide_read(ide_devices[drive].Channel, ATA_REG_ERROR);
      if (st & ATA_ER_AMNF)   {printk("- No Address Mark Found    \n ");   err = 7;}
      if (st & ATA_ER_TK0NF)   {printk("- No Media or Media Error    \n ");   err = 3;}
      if (st & ATA_ER_ABRT)   {printk("- Command Aborted    \n ");      err = 20;}
      if (st & ATA_ER_MCR)   {printk("- No Media or Media Error    \n ");   err = 3;}
      if (st & ATA_ER_IDNF)   {printk("- ID mark not Found     \n");      err = 21;}
      if (st & ATA_ER_MC)   {printk("- No Media or Media Error    \n ");   err = 3;}
      if (st & ATA_ER_UNC)   {printk("- Uncorrectable Data Error    \n ");   err = 22;}
      if (st & ATA_ER_BBK)   {printk("- Bad Sectors    \n ");       err = 13;}
   } else  if (err == 3)           {printk("- Reads Nothing     \n"); err = 23;}
     else  if (err == 4)  {printk("- Write Protected    \n "); err = 8;}
 
   return err;
}

void ide_initialize(unsigned int BAR0, unsigned int BAR1, unsigned int BAR2, unsigned int BAR3, unsigned int BAR4) {
 
   int j, k, count = 0;
 
   // 1- Detect I/O Ports which interface IDE Controller:
   channels[ATA_PRIMARY  ].base  = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
   channels[ATA_PRIMARY  ].ctrl  = (BAR1 & 0xFFFFFFFC) + 0x3F6 * (!BAR1);
   channels[ATA_SECONDARY].base  = (BAR2 & 0xFFFFFFFC) + 0x170 * (!BAR2);
   channels[ATA_SECONDARY].ctrl  = (BAR3 & 0xFFFFFFFC) + 0x376 * (!BAR3);
   channels[ATA_PRIMARY  ].bmide = (BAR4 & 0xFFFFFFFC) + 0; // Bus Master IDE
   channels[ATA_SECONDARY].bmide = (BAR4 & 0xFFFFFFFC) + 8; // Bus Master IDE
   
   // 2- Disable IRQs:
   ide_write(ATA_PRIMARY  , ATA_REG_CONTROL, 2);
   ide_write(ATA_SECONDARY, ATA_REG_CONTROL, 2);
   
     // 3- Detect ATA-ATAPI Devices:
	 int i;
   for (i = 0; i < 2; i++)
      for (j = 0; j < 2; j++) {
 
         unsigned char err = 0, type = IDE_ATA, status;
         ide_devices[count].Reserved = 0; // Assuming that no drive here.
 
         // (I) Select Drive:
         ide_write(i, ATA_REG_HDDEVSEL, 0xA0 | (j << 4)); // Select Drive.
        // sleep(1); // Wait 1ms for drive select to work.
 
         // (II) Send ATA Identify Command:
         ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
        // sleep(1); // This function should be implemented in your OS. which waits for 1 ms.
                   // it is based on System Timer Device Driver.
 
         // (III) Polling:
         if (ide_read(i, ATA_REG_STATUS) == 0) continue; // If Status = 0, No Device.
 
         while(1) {
            status = ide_read(i, ATA_REG_STATUS);
            if ((status & ATA_SR_ERR)) {err = 1; break;} // If Err, Device is not ATA.
            if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ)) break; // Everything is right.
         }
 
         
 
   // 4- Print Summary:
   for (i = 0; i < 4; i++)
      if (ide_devices[i].Reserved == 1) {
         printk(" Found %s Drive\n");
      }else{
	  ide_print_error( i, err);
	  }
	  }
}