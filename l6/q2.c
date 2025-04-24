#include <stdio.h>
#include <stdint-gcc.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/wait.h>

//Sieve of eratothones
/*
    General Approach is that ill send the data through parent once and then child will read 
    the first value and it will check if nothing is there then exit
    else it will send all thenumber which are not multiple of that first number to its own child
    through a new pipe

*/

void sieve(int fd){
    int new_fd[2];
    pipe(new_fd);

    int prime ;
    
    if(read(fd,&prime,sizeof(int))<=0){
        printf("Exiting..\n");
        close(fd);
        exit(0);
    }
   
    printf("%d\n",prime);

    int pid = fork();

    if(pid == 0){
        //child so send the new value
        close(new_fd[1]);
        close(fd);
        sieve(new_fd[0]);
        close(new_fd[0]);
        // wait(NULL);
        exit(0);
    }
    else{
        close(new_fd[0]);
        int buffer;
        while(read(fd,&buffer,sizeof(int))){
            if(buffer % prime != 0)write(new_fd[1],&buffer,sizeof(int));
        }
        close(fd);
        close(new_fd[1]);
        wait(NULL);
        // printf("waiting for this to exit\n");
        exit(0);
    }
}

int main(){

    int n;
    printf("Enter number: ");
    scanf("%d",&n);


    int fd[2];
    pipe(fd);

    int pid = fork();

    if(pid == 0){
        close(fd[1]);
        sieve(fd[0]);  
        close(fd[0]);
         
        wait(NULL);
        exit(0);        
    }
    else{
        close(fd[0]);
        for(int i = 2; i<=n; i++){
            write(fd[1],&i,sizeof(int));
        }
        close(fd[1]);
        wait(NULL);
        // printf("waiting for this to exit\n");
        exit(0);        
    }

}