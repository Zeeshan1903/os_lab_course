#include <semaphore.h>
#include <stdio.h>
#include <stdint-gcc.h>
#include <stdlib.h>
#include <pthread.h>
#include <wait.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
sem_t mutex, write_lock, queue;
int no_reader ;

void* writer(void* arg){
    int id = *(int*)arg+1;

    //first now to ensure fairness we will make each write and reader wait in queue
    sem_wait(&queue);
    sem_wait(&write_lock);                       
    //here we give signal  after writer lock so that if any new wirter comes and os do
    //context switch then still we ill have lock so it won't or other writer won't get the chance of 
    //writing
    sem_post(&queue);

    printf("Wrtiter %d got lck\n",id);
    sleep(5);
    printf("Writer %d finished\n", id);
    sem_post(&write_lock);


    return NULL;
}

void* reader(void* arg){
    int id = *(int*)arg+1;

    sem_wait(&queue);
    sem_wait(&mutex);
    no_reader++;
    if(no_reader == 1){
        sem_wait(&write_lock);
    }
    sem_post(&mutex);
    sem_post(&queue);           //allow others to come
    printf("Reader %d got lock\n",id);
    sleep(rand()% 4  +1);
    printf("Reader %d fininshed\n",id);

    sem_wait(&mutex);
    no_reader--;
    if(no_reader==0){
        sem_post(&write_lock);
    }
    sem_post(&mutex);

    return NULL;
}

int main(){
    pthread_t thread[10];
    no_reader = 0;
    sem_init(&write_lock,0,1);
    sem_init(&mutex,0,1);
    sem_init(&queue,0,1);
    for(int i = 0; i<10; i++){
        int* id = malloc(sizeof(int));
        *id = i+1;
        if(i%4 ==0){
            pthread_create(&thread[i],NULL,writer,id);
        }
        else{
            pthread_create(&thread[i], NULL, reader, id);
        }
    }
    for(int i = 0; i<10; i++)pthread_join(thread[i],NULL);
}