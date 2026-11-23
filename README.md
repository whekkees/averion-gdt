# AVERION GDT

A simple Global Descriptor Table (GDT) implementation for 32-bit x86 operating systems.

## Features

- Kernel code and data segments (Ring 0)
- User code and data segments (Ring 3)
- GDT initialization in C
- GDT loading in x86 Assembly

## Structure

- `include/gdt.h` — GDT structures and declarations
- `src/gdt.c` — GDT initialization
- `src/gdt_flush.asm` — GDT loading routine
