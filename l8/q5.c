/*
    Ticket Lock: Here we are assuming implementation will work for cases mentioned below 
                 and it will have a ticket value and a turn value 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdatomic.h>
#include <pthread.h>

struct ticket{
    int ticket_value;
    int turn_value;
};

void init(struct ticket* t){
    //atomically we have to do everything
    atomic_init(&t->ticket_value,0);
    atomic_init(&t->turn_value,0);
}

void acquire(struct ticket* t){
    //in general what we will do here is get the ticket_value and 
    //then wait in the while loop 
    int my_ticket = atomic_fetch_add(&t->ticket_value,1);
    while(my_ticket != atomic_load(&t->turn_value)){
        sched_yield();
    }

}

struct ticket t;

void release(struct ticket* t){
    atomic_fetch_add(&t->turn_value,1);
}

int counter ;

void* worker(void* arg){

    for(int i= 0; i<100; i++){
        acquire(&t);
        counter++;
        release(&t);
    }

    return NULL;
}

int main(){
   //here we will acquire as well as release the ticket value  
    init(&t);
    int n = 10;
    pthread_t thread[n];
    counter = 0;
    for(int i=0; i<n; i++)pthread_create(&thread[i],NULL,worker,NULL);

    for(int i = 0; i<n; i++)pthread_join(thread[i],NULL);

    printf("Counter Value %d\n",counter);
}