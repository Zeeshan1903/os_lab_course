#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*
    Implementing Semaphore: First of all we will require a lock and cond variable and a vlaue 

*/
struct sem{
    int value;
    pthread_mutex_t lock;
    pthread_cond_t cond;
};

struct sem s;

void init(struct sem* sem, int value){
    sem->value = value;

    pthread_mutex_init(&sem->lock,NULL);
    pthread_cond_init(&sem->cond,NULL);
}

void acquire(struct sem* s){
    //here ill acquire the lock and check if teh value is negative then wait 
    pthread_mutex_lock(&s->lock);

    while(s->value <= 0){
        pthread_cond_wait(&s->cond,&s->lock);
    }
    s->value--;
    pthread_mutex_unlock(&s->lock);
}

void release(struct sem* s){
    pthread_mutex_lock(&s->lock);
    s->value++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->lock);
}


int counter = 0;

void* worker(void* arg){

    for(int i = 0; i<100; i++){
        acquire(&s);
        counter++;
        release(&s);
    }

    return NULL;
}

int main(){
    pthread_t thread[10];
    init(&s,1);

    for(int i = 0;i<10;i++)pthread_create(&thread[i],NULL,worker,NULL);
    for(int i = 0; i<10; i++)pthread_join(thread[i],NULL);
    printf("Counter Value %d\n",counter);
}