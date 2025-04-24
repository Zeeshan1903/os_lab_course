//Orphan process where parent is being terminated and child process still has not finished
//its work

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
    int pid = fork();
    if(pid == 0){
        //child 
        printf("Child %d\n",getpid());
        sleep(10);
    }    
    else{
        printf("Parent section exiting...\n");
        exit(0);
    };

}