@echo off
@echo ***NixelOS Windows Compiler***
    echo --Compilling bootloader
    
@echo Part 1.Clearing Cache
    cd binary
	del *.o
	cd ..
@echo Part 2.Compiling kernel
    dev\compillers\nasm -f elf32 -o binary/kasm.elf kernel/kasm.asm
    dev\compillers\mingw\bin\g++ -c kernel/kernel.cpp -o binary/kernel.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/init.cpp -o binary/init.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/panic.cpp -o binary/panic.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/memory.cpp -o binary/memory.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/graphics.cpp -o binary/graphics.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/tty.cpp -o binary/tty.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\gcc -c kernel/kbd.cpp -o binary/kbd.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/libc++/io.cpp -o binary/io.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/fs/VFS.cpp -o binary/VFS.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/lakesh/lakesh.cpp -o binary/lsh.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/isr.cpp -o binary/isr.o -Wall -Wextra -nostdlib
    dev\compillers\mingw\bin\g++ -c kernel/debug.cpp -o binary/debug.o -Wall -Wextra -nostdlib
@echo Part 3.Compiling stdint modules and linking
    dev\compillers\mingw\bin\g++ -c stdint/string.c -o binary/libc/string.o -Wall -Wextra -nostdlib    

    echo --Linking kernel
	dev\compillers\mingw\bin\ld -Tlink.ld -o binary/krnl.out binary/kernel.o binary/io.o binary/isr.o binary/debug.o binary/kbd.o binary/lsh.o binary/panic.o binary/init.o binary/memory.o binary/graphics.o  binary/tty.o binary/kasm.elf binary/libc/string.o binary/VFS.o
    dev\compillers\mingw\bin\objcopy -I elf32-i386 binary/krnl.out binary/kernel.elf
@echo ***NixelOS Windows Compiler***
@pause