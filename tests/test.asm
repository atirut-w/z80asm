section .data
    hello: db "Hi Mom!", 10  ; string to print
    helloLen: equ $-hello    ; length of the string

section .text
    global _start       ;entry point for linker

    _start:
        ld    a,1          ; sys_write
        ld    bc,1         ; stdout
        ld    de,hello     ; message to write
        ld    hl,helloLen  ; message length
        rst   38h          ; call kernel

        ; end program
        ld    a,60         ; sys_exit
        ld    b,0          ; error code 0 (success)
        rst   38h          ; call kernel
