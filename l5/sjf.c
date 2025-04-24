#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

#define PROCESS_LIST 100
#define SIZE 1000

struct Task {
    char input_time[SIZE];
    int time[SIZE];
    int total_count;

};
struct ProcessInfo{
    char pid[3];
    int arrival_time;
    struct Task task;
};

int compare_time(const void* a, const void* b){
    const struct ProcessInfo* p1 = (struct ProcessInfo* )a;
    const struct ProcessInfo* p2 = (struct ProcessInfo* )b;

    return p1 -> arrival_time - p2 -> arrival_time;

}

int total_time(struct ProcessInfo* p){
    int time = 0;
    for(int i = 0; i<p->task.total_count; i++)time+=p->task.time[i];

    return time;
}
int compare_total_time(const void* a, const void* b){
    const struct ProcessInfo* p1= (struct ProcessInfo* )a;
    const struct ProcessInfo* p2 = (struct ProcessInfo* )b;

    return total_time(p1) - total_time(p2);
}
void parse_line(struct ProcessInfo* process, char* line){
    char* token = strtok(line , " ");
    strcpy(process -> pid, token);
    token = strtok(NULL," ");
    process -> arrival_time = atoi(token);

    int count = 0;

    while((token = strtok(NULL, " "))){
        process -> task.input_time[count] = token[0];
        token = strtok(NULL, " ");
        process -> task.time[count]= atoi(token);
        count++;
    }

    process -> task. total_count = count;

}


void print_process(struct ProcessInfo proc[], int count){
    // printf("hola\n");
    // if()
    for(int i = 0; i<count; i++){
        // if(proc[i] == )return
        printf("P%c %d", proc[i].pid[1], proc[i].arrival_time);
        
        for(int j = 0; j<proc[i].task.total_count; j++){
            if(proc[i].task.input_time[j] == '\0')break;
            printf(" %c %d", proc[i].task.input_time[j], proc[i].task.time[j]);
        }
        printf("\n");
    }
}

void print(struct ProcessInfo* proc, int resp,int turn){
    printf("%s response_time %d, turnaround_time %d\n", proc -> pid, resp, turn );
}

int response_time(struct ProcessInfo* proc, int current_time ){
    return current_time - proc -> arrival_time;
}
int turnaround_time(struct ProcessInfo* proc, int current_time){
    return current_time + total_time(proc) - proc->arrival_time;
}
void sjf(struct ProcessInfo proc[], int count){
    qsort(proc, count, sizeof(struct ProcessInfo), compare_time );
    int current_time = 0;

    int visited[count];
    int completed = 0;
    for(int i = 0; i<count; i++)visited[i]  = 0;
    while(completed < count) {
        struct ProcessInfo new_process[100];
        int j = 0;
        
        
        for(int i = 0;i<count; i++){
            if(!visited[i] && proc[i].arrival_time <= current_time){
                // printf("inside forloopg\n");
                new_process[j++]=proc[i];
            }
        }         

        qsort(new_process, j, sizeof(struct ProcessInfo), compare_total_time);
        struct ProcessInfo p = new_process[0];
        int k;
        for(k = 0; k<count; k++){
            if(strcmp(proc[k].pid, p.pid) == 0  && !visited[k]){
                visited[k] = 1;
                break;
            }
        }
        // printf("k: %d\n", k);
        
        int resp = response_time(&proc[k], current_time);
        int turn_a = turnaround_time(&proc[k], current_time);
        print(&proc[k], resp, turn_a );
        current_time += total_time(&proc[k]);
        completed++;

    }
}
int main(){

    struct ProcessInfo process[PROCESS_LIST];
    char line[100];

    FILE* file = fopen("input.txt", "r");
    int index = 0;
    int counter = 5;
    while(counter--){
        // if(line[0] == '\n')continue;

        // line[strcspn(line, "\n")] = '\0';
        if(index == 3 ) process[index].arrival_time = 0;
        else process[index].arrival_time = rand() % 8;
        process[index].pid[0] = 'P';
        char c [2];
        sprintf(c,  "%d", counter);
        process[index].pid[1] = c[0];
        int no_proc = rand() % 7;
        for(int u = 0;u < no_proc ; u++){
            process[index].task.input_time[u] = 'C';
            process[index].task.time[u] = rand() % 10;
        }
        // parse_line(&process[index], line);
        process[index].task.total_count = no_proc;
        index++;
    }
    print_process(process, index);
    sjf(process, index);
}