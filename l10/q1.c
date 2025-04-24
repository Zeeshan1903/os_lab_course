#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void print(const char* path){
 //   struct dirent* entry;
//    DIR* d = opendir(path);
    struct  stat statbuf;

    if(stat(path,&statbuf) == -1){
        printf("Error while creating the file\n");
        return;
    }

    printf("File name %s\n, size %ld\t block_size %ld\n",path,statbuf.st_size,statbuf.st_blksize);

}

int main(){
    const char* path = "/home/zeeshan/Desktop/practise_os_lab_end_sem/l10";
    print(path);
}