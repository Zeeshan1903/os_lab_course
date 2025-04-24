.global _start
.extern trap_handler
.extern kernel_main

_start:
    la sp, stack_top

    la t0, trap_handler
    csrw mtvec, t0

    call kernel_main

    j .
    .section .bss
    .space 4096
    .align 4

stack_top:
