#include <stdint.h>
#define UART 0x10000000
#define MTIME  0x0200bff8
#define MTIME_CMP 0x02004000
#define TIME 10000000


void trap(){
    *(volatile uint64_t* )MTIME_CMP = TIME + *(volatile uint64_t*)MTIME;

    char* str = "Hello World\n";

    while(*str != '\0'){
        *(volatile char*)UART = *str;
        str++;
    }

}

void kernel_main(){

    *(volatile uint64_t* )MTIME_CMP = TIME + *(volatile uint64_t*)MTIME;

    asm volatile(
        "li t0, 0x80\n"
        "csrw mie, t0\n"
        "li t0, 0x08\n"
        "csrw mstatus,t0\n"
    );

    while(1);
}