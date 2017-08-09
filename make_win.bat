@echo off
@echo ***NixelOS Windows Compiler***

@echo Part 1.Compiling boot loaders

@echo Part 2.Compiling kernel
    echo --Compilling entry point
    dev\compillers\nasm -f elf32 -o binary/kasm.elf kernel/kasm.asm
	
    echo --Compilling kernel.cpp
    dev\compillers\mingw\bin\g++ -c kernel/kernel.cpp -o binary/kernel.o -Wall -Wextra -nostdlib

    echo --Compilling init.cpp
    dev\compillers\mingw\bin\g++ -c kernel/init.cpp -o binary/init.o -Wall -Wextra -nostdlib

    echo --Compilling gdt.cpp
    dev\compillers\mingw\bin\g++ -c kernel/gdt.cpp -o binary/gdt.o -Wall -Wextra -nostdlib

    echo --Compilling panic.cpp
    dev\compillers\mingw\bin\g++ -c kernel/panic.cpp -o binary/panic.o -Wall -Wextra -nostdlib
	
    echo --Compilling memory.cpp
    dev\compillers\mingw\bin\g++ -c kernel/memory.cpp -o binary/memory.o -Wall -Wextra -nostdlib

    echo --Compilling graphics.cpp
    dev\compillers\mingw\bin\g++ -c kernel/graphics.cpp -o binary/graphics.o -Wall -Wextra -nostdlib
	
    echo --Linking kernel
	dev\compillers\mingw\bin\ld -Tlink.ld -o binary/krnl.out binary/kernel.o binary/panic.o  binary/init.o binary/memory.o binary/graphics.o binary/gdt.o binary/kasm.elf
    dev\compillers\mingw\bin\objcopy -I elf32-i386 binary/krnl.out binary/kernel.elf
@echo ***NixelOS Windows Compiler***
@pause