    ld a, 255
    ; TODO: Bother z88dk devs to add something to accomodate this bodge
    ld bc, 2 ; Page 2 remap register
    ld d, 0 ; Current bank we're testing
    ld hl, 0x2000 ; Address to test on

memcheck_loop:
    out (c), d

    ld (hl), 0x55
    ld a, (hl)
    cp 0x55
    jr z, memcheck_ok

    inc d
    jr nz, memcheck_loop
nomem:
    halt ; No point in continuing, we're toast
    jr nomem
memcheck_ok:
