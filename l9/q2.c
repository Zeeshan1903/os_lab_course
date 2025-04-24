#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int total_worker;

sem_t sem;
sem_t mutex;
void thr_signal(){
    sem_post(&mutex);
}
void thr_join(){
    sem_wait(&mutex);
}
void* worker(void* arg){

    sem_wait(&sem);
    total_worker++;
    printf("Current total_worker %d\n",total_worker);
    sem_post(&sem);
    sleep(1);
    if(total_worker == 10){
        thr_signal();
    }
    return NULL;
}

int main(){
    sem_init(&mutex,0,0);
    sem_init(&sem,0,1);
    pthread_t thread[10];
    total_worker = 0;
    for(int i = 0; i<10; i++)pthread_create(&thread[i],NULL,worker,NULL);

    //crross this line after all thread finishes their work
    thr_join();
}