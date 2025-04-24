//Zombie Process: Means child has exited gracefully but parent is not waiting for it 
//so main systemd will takeover this process

#include <stdio.h>
#include <stdint-gcc.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int main(){
    int pid = fork();

    if(pid == 0){
        //child 
        printf("Child %d\n",getpid());
        exit(0);
    }
    else{
        printf("Parent section \n");
        sleep(10);                      //to simulate some work is being done 
        
    }
}