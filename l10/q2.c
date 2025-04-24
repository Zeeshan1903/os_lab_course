#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/stat.h>
#include <string.h>

void print_permission(mode_t mode){

    char perm[10] = "---------";

    if(mode & S_IRUSR)perm[0] = 'r';
    if(mode & S_IWUSR)perm[1] = 'w';
    if(mode & S_IXUSR)perm[2] = 'x';
    if(mode & S_IRGRP)perm[3] = 'r';
    if(mode & S_IWGRP)perm[4] = 'w';
    if(mode & S_IXGRP)perm[5] = 'x';
    if(mode & S_IROTH)perm[6] = 'r';
    if(mode & S_IWOTH)perm[7] = 'w';
    if(mode & S_IXOTH)perm[8] = 'x';

    printf("Permission %s\n",perm);
}

void print(const char* path){

    struct stat statbuf;

    struct dirent* entry;
    DIR* d = opendir(path);

    while(entry = readdir(d)){
        if(strcmp(".",entry->d_name)  == 0 || strcmp("..",entry->d_name)  == 0)continue;

        char input[1000];
        snprintf(input,sizeof(input),"%s/%s",path,entry->d_name);

        if(stat(input,&statbuf) == -1)return;

        printf("%s \t\t",entry->d_name);
        print_permission(statbuf.st_mode);

        if(S_ISDIR(statbuf.st_mode))print(input);

    }
    closedir(d);
}

int main(){
    int permission =1;
    const char* path = "//home/zeeshan/Desktop/practise_os_lab_end_sem";

    print(path);
}