@echo off
@echo ***NixelOS Windows Compiler***

@echo Part 1.Compiling boot loaders

@echo Part 2.Compiling kernel
    echo --Compilling entry point
    dev\compillers\nasm -f elf32 -o binary/kasm.elf boot/kernel/kasm.asm
    echo --Compilling kernel.c
    dev\compillers\mingw\bin\gcc -c boot/kernel/kernel.c -o binary/kernel.o -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32
    echo --Compilling tty.c
    dev\compillers\mingw\bin\gcc -c boot/kernel/tty.c -o binary/tty.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    echo --Compilling kbd.c
    dev\compillers\mingw\bin\gcc -c boot/kernel/kbd.c -o binary/kbd.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    echo --Compilling shell.c
    dev\compillers\mingw\bin\gcc -c boot/kernel/shell/shell.c -o binary/shell.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    echo --Compilling logs.c
    dev\compillers\mingw\bin\gcc -c boot/kernel/logs.c -o binary/logs.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    echo --Compilling io.c
    dev\compillers\mingw\bin\gcc -c boot/kernel/io.c -o binary/io.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    echo --Compilling Speaker.c
    dev\compillers\mingw\bin\gcc -c boot/kernel/Speaker.c -o binary/Speaker.o -Wall -Wextra -std=c99 -nostdlib -nostartfiles -nodefaultlibs -m32
    echo --Compilling graphics.c
	dev\compillers\mingw\bin\gcc -c boot/kernel/NixelDraw/graphics.c -o binary/graphics.o -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -m32
    echo --Linking kernel
	dev\compillers\mingw\bin\ld -Tlink.ld -o binary/krnl.out binary/kernel.o binary/shell.o binary/logs.o binary/kbd.o binary/io.o binary/tty.o binary/Speaker.o binary/graphics.o binary/kasm.elf
    dev\compillers\mingw\bin\objcopy -I elf32-i386 binary/krnl.out binary/kernel.elf
@echo ***NixelOS Windows Compiler***
@pause