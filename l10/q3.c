/*
    My tail: General approach will be we will first take teh position and then we will use SEEK_SET 
    to set 
*/
#include <stdio.h>
#include <stdint-gcc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void print(int fd){
    char buffer;
    if(read(fd,&buffer, sizeof(char)) <= 0)return;
    printf("%c", buffer);
    print(fd);
}

void my_tail(int fd,int no_lines){
    int size = lseek(fd,0,SEEK_END);
    size--;
    int lines = 0;
    
    while(lines < no_lines && size >=0 ){
        lseek(fd,size,SEEK_SET);
        char buffer;
        if(read(fd,&buffer,sizeof(char))<=0)break;

        if(buffer == '\n')lines++;
        size--;
    }
    // printf("Exiting\n");
    size+=2;
    lseek(fd,size,SEEK_SET);
         
}

int main(){
    const char* path = "a.txt"; 
    int fd = open("a.txt", O_RDONLY);
    int no_lines = 10;
    // printf("Waiting\n");
    my_tail(fd,no_lines);
    print(fd);

}