#include <stdio.h>
#include <pthread.h>
#include <search.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

sem_t sem,queue;
int no_thread ;
int total;

void barrier(){

    sem_wait(&sem);
    no_thread++;
    if(no_thread < total){
        sem_post(&sem);
        sem_wait(&queue);
        sem_wait(&sem);
    }

    sem_post(&queue);
    sem_post(&sem);

}


void* worker(){
    printf("p1\n");
    sleep(1);
    barrier();
    printf("p2\n");
}

int main(){
    sem_init(&sem,0,1);
    sem_init(&queue,0,0);
    int n = 10;
    no_thread = 0;
    total = n;
    pthread_t thread[n];

    for(int i = 0; i<n; i++)pthread_create(&thread[i],NULL,worker,NULL);

    for(int i = 0; i<n; i++)pthread_join(thread[i],NULL);


}