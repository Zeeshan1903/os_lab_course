#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/*
    Lottery Scheduling: Here we will run the whole scheduler for summation of total_ticket value * 2 
                        times so that we can see it is working 

*/

struct process{
    int ticket_value;
};

struct process* generate_process(struct process* p, int total_process){

    for(int i =0; i<total_process; i++){
        p[i].ticket_value = rand() % 10 + 1;
    }

    return p;
}

void print_process(struct process* p, int total_process){
    for(int i = 0; i<total_process; i++)printf("P%d, ticket_value %d\n",i,p[i].ticket_value);

    printf("\n");
}

void scheduling(struct process* p, int total_process){
    int total_ticket = 0;

    for(int  i = 0; i<total_process; i++)total_ticket+=p[i].ticket_value;
    int t_ticket = total_ticket;
    total_ticket = total_ticket*2;

    int freq[total_process];
    for(int i = 0; i<total_process; i++)freq[i] = 0;

    while(total_ticket){

        int current_ticket_value = rand() % t_ticket;

        int counter = 0;
        for(int i = 0; i<total_process; i++){
            counter+=p[i].ticket_value;
            if(counter >= current_ticket_value){
                printf("P%d scheduled\n",i);
                freq[i]++;
                break;
            }
        }
        total_ticket--;
    }

    for(int i = 0; i<total_process; i++)printf("\nFreq of P%d, is %d\n",i,freq[i]);

}

int main(){
    srand(time(NULL));
    int total_process = rand() % 5 + 1;
    struct process* p = malloc(sizeof(struct process)* total_process);

    p = generate_process(p,total_process);
    print_process(p,total_process);

    scheduling(p,total_process);

}