#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <string.h>
#include <time.h>
#include <limits.h>

//Considering only CPU jobs 
/*
    Stride: Each process will have a counter_value, ticket_value, stride_value
        Stride_value(i) = lcm of all the tickets/(ticket_value(i))
        then each time run the scheduler and pick the process that have minimum counter_value 
        and update the counter_value 
        counter_value(i) += stride_value(i)
*/

struct process{
    int stride_value;
    int counter_value;
    int ticket_value;
};

struct process* generate_process(struct process* p,int size){
    for(int i = 0; i<size;i++){
        p[i].ticket_value = rand() % 5 + 1;                         //so that ticket should not be zero
        p[i].stride_value = p[i].counter_value = 0;
    }
    return p;
}

struct process* calculate_lcm(struct process* p,int size){
    int lcm_value =1 ;
    for(int i = 0; i<size; i++){
        lcm_value *= p[i].ticket_value;
    }

    //now update the value of each of them 
    for(int i = 0; i<size; i++){
        p[i].stride_value = lcm_value/p[i].ticket_value;
    }

    return p;
}
    

void print_process(struct process* p, int size){
    for(int i = 0; i<size; i++){
        printf("P%d, ticket_value: %d\n",i,p[i].ticket_value);
    }

}

int check_end_process(struct process* p, int size){
    for(int i = 0; i<size; i++){
        if(p[i].counter_value != p[i].ticket_value * p[i].stride_value)return 0;
    }
    return 1;
}

void scheduling(struct process* p, int size){

    while(1){
        if(check_end_process(p,size))return;

        int p_index = 0, mini = INT_MAX;
        for(int i =0; i<size; i++){
            if(mini > p[i].counter_value){
                mini = p[i].counter_value ;
                p_index = i;
            }
        }

        p[p_index].counter_value += p[p_index].stride_value;

        for(int i = 0; i<size; i++)printf("%d ",p[i].counter_value);
        printf("\n");
    } 

}


int main(){
    int total_process =  rand() % 5 + 1;                //atleast one process 
    srand(time(NULL));

    struct process* p  = malloc(sizeof(struct process)* total_process); 

    p = generate_process(p,total_process);
    p = calculate_lcm(p,total_process);

    for(int i = 0; i<total_process; i++)printf("P%d ",i);
    
    printf("\n");
    
    scheduling(p,total_process);
  
}