#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

sem_t reader, writer;
int no_reader = 0;
void* read_work(void*arg){
    int id = *(int *)arg;
    sem_wait(&reader);
    no_reader++;
    if(no_reader == 1){
        sem_wait(&writer);
    } 

    sem_post(&reader);
    printf("Reader doing workd %d\n",id);
    sleep(1);
    printf("Reader %d completed\n",id);
    sem_wait(&reader);
    no_reader--;
    if(no_reader == 0)sem_post(&writer);
    sem_post(&reader);

}

void* write_work(void* arg){

    int id = *(int *)arg;

    sem_wait(&writer);
    printf("Writer %d acquire\n",id);
    sleep(2);
    printf("wrtier %d released\n",id);
    sem_post(&writer);
}

int main(){
    sem_init(&reader,0,1);
    sem_init(&writer,0,1);
    no_reader = 0;
    pthread_t thread[10];

    int natural[10];
    for(int i = 0; i<10; i++)natural[i] = i+1;

    for(int i = 0; i<10; i++){
        if(i % 3 == 0)pthread_create(&thread[i],NULL,write_work,&natural[i]);
    
        else pthread_create(&thread[i],NULL,read_work,&natural[i]);
    }

    for(int i = 0; i<10; i++)pthread_join(thread[i],NULL);
}