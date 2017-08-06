@echo off
@echo ***NixelOS Windows Compiler***

@echo Part 1.Compiling boot loaders

@echo Part 2.Compiling kernel
    echo --Compilling entry point
    dev\compillers\nasm -f elf32 -o binary/kasm.elf kernel/kasm.asm
	
    echo --Compilling kernel.cpp
    dev\compillers\mingw\bin\g++ -c kernel/kernel.cpp -o binary/kernel.o -Wall -Wextra -nostdlib
	
    echo --Linking kernel
	dev\compillers\mingw\bin\ld -Tlink.ld -o binary/krnl.out binary/kernel.o binary/kasm.elf
    dev\compillers\mingw\bin\objcopy -I elf32-i386 binary/krnl.out binary/kernel.elf
@echo ***NixelOS Windows Compiler***
@pause