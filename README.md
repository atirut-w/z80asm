# Z80ASM
An attempt at making a Z80 assembler that outputs to ELF format. WIP.

Currently, the assembler only support several instructions
- `LD r, n`
- `LD r, r`
- `HALT`

I'll try to support more instructions as I develop the assembler, but I am sometimes busy unspaghettifying my codes, so it'll bake some times.

## Build dependencies
- *A* C++ compiler
- CMake
- ANTLR4 >= 4.10.1

If you're on Windows, good luck installing the dependencies. [Chocolatey](https://chocolatey.org/) *may* save you from hell. If you're on Linux, be sure to pick the devel version of the required libraries.
