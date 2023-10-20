section .data
    hello: db "Hi Mom!", 10  ; string to print
    helloLen: equ $-hello    ; length of string

section .text
    global _start
    start:
        mov a, 1          ; sys_write
        mov bc , 1        ; stdout
        mov de, hello     ; message to write
        mov hl, helloLen  ; message length
        rst 0x08          ; call kernel

        mov a, 60         ; sys_exit
        mov bc, 0         ; error code 0 (success)
        rst 0x08          ; call kernel
