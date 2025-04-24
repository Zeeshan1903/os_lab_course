#define UART 0x10000000UL
#include <stdint.h>

char get_key(){
    volatile unsigned char* uart = (volatile char*)UART;

    while(!(*(uart+5)& 0x01));

    return *uart;
}

void kernel_main(){
    //keyboard 
    
    while(1){
        char c = get_key();
        *(volatile char*)UART = c;
    }
    
}