#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/wait.h>

int main(){
    int fd1[2],fd2[2];
    pipe(fd1);
    pipe(fd2);

    int pid = fork();

    int value = 10;

    //Parent send the integer through fd1 and thenchild through fd2

    if(pid == 0){
        //child will send the value
        //read the value
        
        close(fd1[1]);                                  //First child will read 
                                                        //As pipes are blocking so it will wait until data is available
        int buffer;
        read(fd1[0],&buffer,sizeof(int));
        close(fd1[0]);
        printf("Child received %d\n",buffer);
        buffer += 10;

        close(fd2[0]);
        write(fd2[1],&buffer,sizeof(int));
        close(fd2[1]);

        exit(0);
    }
    else{

        close(fd1[0]);
        write(fd1[1],&value,sizeof(int));
        close(fd1[1]);

        int buffer =0;

        close(fd2[1]);
        read(fd2[0],&buffer, sizeof(int));
        close(fd2[0]);

        printf("Parent received %d\n",buffer);
        wait(NULL);        
    }
    printf("Exiting....\n");
}