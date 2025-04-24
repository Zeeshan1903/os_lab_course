#include <stdio.h>
#include <stdlib.h>
#include<wait.h>
#include <time.h>
#include <limits.h>

struct ProcessInfo{
    int pid;
    int arrival_time;
    int burst_time;
    int  completed;
};

int compare_time(const void*a, const void* b){
    const struct ProcessInfo* p1 = (struct ProcessInfo *)a;
    const struct ProcessInfo* p2 = (struct ProcessInfo *)b;
    return p1->arrival_time - p2->arrival_time;
}
void sjtf(struct ProcessInfo process[], int count){
    
    //first of all here add the current time of all the processes in the burst time vector 
    //so that we can keep a counter in the array 
    int completed = 0;
    int current_time = 0;
    int burst_time[count];

    qsort(process, count, sizeof(struct ProcessInfo), compare_time);
    for(int i = 0; i<count;  i++){
        burst_time[i] = process[i].burst_time;
    }

    while(completed < count){
        
        int index = -1;
        //now i ll take the process which willhave least value as the of arrival_time < current_time 
        for(int i= 0; i<count; i++){
            if(!process[i].completed && process[i].arrival_time <= current_time){
                if(index == -1 || burst_time[i] < burst_time[index]){

                    index = i;
        
                }
                // break;
            }
        }

        if(index == -1){
            //means no job was there so go on and find the next_job 
            int first_job_arriva_time = INT_MAX;
            for(int k = 0; k<count;k++){
                if(!process[k].completed && process[k].arrival_time >current_time){
                    if(process[k].arrival_time < first_job_arriva_time){
                        first_job_arriva_time = process[k].arrival_time;
                    }
                }
            }
            current_time = first_job_arriva_time;
        }

        else{

            // process[index].burst_time--;
            current_time++;
            burst_time[index]--;
            if(burst_time[index ] == 0){
                process[index].completed = 1;
                printf("P%d response_time %d and turnaround_time %d\n", process[index].pid, current_time - process[index].arrival_time  , current_time + process[index].burst_time - process[index].arrival_time);
                completed++;
            }

        }






    }
}

void print(struct  ProcessInfo process[], int count)
{
    printf("Inside the print fn\n");
    for(int i = 0;i<count; i++){
        printf(" i %d --->P%d, arrival_time %d, burst_time %d\n", i, process[i].pid, process[i].arrival_time, process[i].burst_time);
    }   
}

int main(){
    srand(time(NULL));
    int no_process = rand() % 6 + 3;
    struct ProcessInfo process[no_process];
    printf("No process --> %d\n", no_process);
    for(int i = 0; i<no_process; i++){
        process[i].pid = i;
        // process[i].arrival_time = 0;
        process[i].arrival_time = rand()% 10;
        process[i].burst_time = rand()% 10 + 1;
        process[i].completed = 0; 
    }

    print(process, no_process);
    sjtf(process, no_process);
    printf("\n\nPrinting after sjtf--------------\n\n");
    print(process, no_process);
}

