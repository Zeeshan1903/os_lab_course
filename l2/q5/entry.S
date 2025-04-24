.global _start
.extern kernel_main
_start:
    la sp,  stack_top

    call kernel_main

    j .
    .section .bss
    .align 4
    .space 4096 

stack_top:
