# MUIC - DPS - Laboratorio 1

## ejemplo1.c

Follow the instructions explained in the beginning of file ejemplo1.c for compiling with gcc and g++ (you can try also clang). 

The file ejemplo1-c11.c has the rules and recommendations of the code
The file ejemplo1-c11.c has the fixes to compile without warnings and errors using the compiler gcc with standard C11 and using -Wall
The file ejemplo1-g++.c has the fixes to compile without warnings and errors using the compiler g++ and using -Wall

## ejemplo2.c. Program Instrumentation

Find the memory errors presented in file ejemplo2 using gcc instrumentation option **AddressSanitizer (ASan)**.
Explain in this file each error.


Have used this command to compile the file:
gcc ejemplo2.c -fsanitize=address -static-libasan -g

These are the solutions to the tested options
    1: Everything's fine
    2: ==3907==ERROR: LeakSanitizer: detected memory leaks
        We don't use free to liberate the memory

    3: ==3924==ERROR: AddressSanitizer: heap-use-after-free on address 0x60b0000000f0 at pc 0x55ef1f586e7d bp 0x7fffc2231260 sp 0x7fffc2230a08
        We use the free before we have already accessed

    4: ==3947==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x603000000022 at pc 0x56377f047e7d bp 0x7ffe3b6207c0 sp 0x7ffe3b61ff68
        The size of the memory we reserve isn't enough to contain the char because the '\0' is left out
