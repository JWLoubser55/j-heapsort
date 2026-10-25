# Heapsort
A basic heapsort implementation for x86-64 Linux
Requires nasm
Builds with clang or gcc

# Using as-is
```sh
nasm -f elf64 move.asm
cc <flags> hsort.c move.o
```
