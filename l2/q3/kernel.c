#include <stdint.h>

#define UART 0x10000000

void kernel_main(){

    char* str = "Hello world\n";

    while (*str != '\0')
    {
        *(volatile char*)UART = *str;
        str++; 
    }
     

}