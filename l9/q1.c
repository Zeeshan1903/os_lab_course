#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

sem_t empty, full, mutex;
int *producerdone;
int* buffer;
int in=0, out=0 , buffersize;

void *producera(void *arg){
    int id = *(int *)arg;
    free(arg);
    for (int i = 0; i < 10; i++){
        int item = (id+1)*i;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        in = (in+1)%buffersize;
        sem_post(&mutex);
        sem_post(&full);
    }
    sem_wait(&mutex);
    producerdone[id]=1;
    sem_post(&mutex);
    return NULL;
}

void* consumera(void *arg){
    int id = *(int *)arg;
    free(arg);
    while(1){
        sem_wait(&full);
        sem_wait(&mutex);

        int alldone =1;
        for (int i = 0; i < buffersize; i++){
            if (!producerdone[i]){
                alldone =0;
                break;
            }
        }
        if(alldone && (in == out)){
            sem_post(&mutex);
            sem_post(&full);
            break;
        }

        int item = buffer[out];
        if(item % (id+1)==0){
            printf("Thread %d consuming %d \n" , id , item);
            out = (out+1)%buffersize;
            sem_post(&empty);
        }else{
            sem_post(&full);
        }
        sem_post(&mutex);
    }
    return NULL;
}

int main(){
    int n;
    scanf("%d" , &n);
    buffersize =n;
    buffer =(int *)malloc(sizeof(int)*n);
    producerdone =(int *)malloc(sizeof(int)*n);
    pthread_t producer[n];
    pthread_t consumer[n];
    sem_init(&empty ,0 ,n);
    sem_init(&full ,0 ,0);
    sem_init(&mutex ,0 ,1);
    for (int i = 0; i < n; i++){
        producerdone[i]=0;
    }
    for (int i = 0; i < n; i++){
        int *id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&producer[i],NULL , producera, id);
    }
    for (int i = 0; i < n; i++){
        int *id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&consumer[i],NULL , consumera, id);
    }
    for (int i = 0; i < n; i++){
        pthread_join(producer[i],NULL);
        pthread_join(consumer[i],NULL);
    }

    return 0;
}