#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>

/*
    Printing the dir 
*/

void print(const char* path,int depth){
    struct dirent* entry;
    DIR* d = opendir(path);
    struct stat statbuf;

    while(entry = readdir(d)){
        //here we will skip for . and ..
        if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)continue;

        char input[1000];
        snprintf(input,sizeof(input),"%s/%s",path,entry->d_name);

        for(int i = 0;i<=depth; i++)printf("|---");
        printf("%s\n",entry->d_name);


        if(stat(input,&statbuf) == -1)return;

        if(S_ISDIR(statbuf.st_mode)){
            print(input,depth+1);
        }

    }
    closedir(d);
}

int main(){

    const char* path = "//home/zeeshan/Desktop/practise_os_lab_end_sem";
    print(path,0);

}