#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>
sem_t a,b;

void* worker1(void* arg){

    printf("Proess A\n");
    sleep(5);
    sem_wait(&b);
    sem_post(&a);

    printf("Process A exited\n");
    return NULL;
}

void* worker2(void* arg){

    printf("Process B\n");
//    sleep(3);

    sem_post(&b);
    sem_wait(&a);

    printf("Process B exited\n");
    return NULL;
}

int main(){

    sem_init(&a,0,0);
    sem_init(&b,0,0);
    
    pthread_t thread[2];
    for(int i = 0;i<2; i++){
        if(i == 0)pthread_create(&thread[i],NULL,worker1,NULL);
        else pthread_create(&thread[i],NULL,worker2,NULL);
    }

    for(int i = 0; i<2;i++)pthread_join(thread[i],NULL);


}