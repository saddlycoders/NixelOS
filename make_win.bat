@echo off
@echo ***NixelOS Windows Compiler***

@echo Part 1.Compiling boot loaders
    dev\compillers\nasm -O0 -f bin -o binary/mbr.bin boot/loader/mbr.asm
    dev\compillers\nasm -O0 -f bin -o binary/FAT32.bin boot/loader/FAT32.asm
    dev\compillers\nasm -O0 -f bin -o binary/setup.bin boot/loader/setup.asm
@echo Part 2.Compiling kernel
    dev\compillers\nasm -f elf32 -o binary/kasm.elf boot/kernel/kasm.asm
    dev\compillers\mingw\bin\gcc -c boot/kernel/kernel.c -o binary/kernel.o -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32
    dev\compillers\mingw\bin\gcc -c boot/kernel/tty.c -o binary/tty.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    dev\compillers\mingw\bin\gcc -c boot/kernel/kbd.c -o binary/kbd.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    dev\compillers\mingw\bin\gcc -c boot/kernel/io.c -o binary/io.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    dev\compillers\mingw\bin\gcc -c boot/kernel/logs.c -o binary/logs.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    dev\compillers\mingw\bin\gcc -c boot/kernel/console.c -o binary/console.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    dev\compillers\mingw\bin\gcc -c boot/kernel/Speaker.c -o binary/Speaker.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
	dev\compillers\mingw\bin\gcc -c boot/kernel/idt.c -o binary/idt.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
	dev\compillers\mingw\bin\gcc -c boot/kernel/CMOS.c -o binary/CMOS.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
	dev\compillers\mingw\bin\gcc -c boot/kernel/NixelDraw/print.c -o binary/print.o -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32
	dev\compillers\mingw\bin\gcc -c boot/kernel/NixelDraw/cls.c -o binary/cls.o -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32
	dev\compillers\mingw\bin\gcc -c boot/kernel/NixelDraw/graphics.c -o binary/graphics.o -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32
	dev\compillers\mingw\bin\ld -Tlink.ld -o binary/krnl.out binary/kernel.o binary/cls.o binary/CMOS.o binary/idt.o binary/print.o binary/logs.o binary/kbd.o binary/VBE.o binary/tty.o binary/Speaker.o binary/io.o binary/console.o binary/graphics.o binary/kasm.elf
    dev\compillers\mingw\bin\objcopy -I elf32-i386 binary/krnl.out binary/kernel 
@echo ***NixelOS Windows Compiler***
@pause