#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int starting_time;
    int exit_time;
    int waiting_time;
} process;

// Comparison of two processes by their arrival time
// Id field has been used to make qsort() stable
int compare(const void *a, const void *b) {
    process **m = (process**) a;
    process **n = (process**) b;
    if ((*m)->arrival_time == (*n)->arrival_time)
        return ((*m)->id < (*n)->id) ? -1 : 1;
    return ((*m)->arrival_time < (*n)->arrival_time) ? -1 : 1;
}

// Max of two values
int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    process **inp_proc; // Contain processes in the order of their entering
    process **proc; // Contain processes in sorted order (by arrival time)
    int number_of_processes;

    printf("Enter the number of processes:\n");
    scanf("%d", &number_of_processes);

    // Initializing inp_proc and proc
    proc = malloc(number_of_processes * sizeof(process*));
    inp_proc = malloc(number_of_processes * sizeof(process*));
    for (int i = 0; i < number_of_processes; ++i)
        inp_proc[i] = malloc(sizeof(process));

    // Requiring input
    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < number_of_processes; ++i) {
        printf("Enter the arrival time of process %d:\n", i+1);
        scanf("%d", &(inp_proc[i]->arrival_time));
        printf("Enter the burst time of process %d:\n", i+1);
        scanf("%d", &(inp_proc[i]->burst_time));
        inp_proc[i]->id = i;
    }

    // Copying inp_proc to proc
    for (int i = 0; i < number_of_processes; ++i)
        proc[i] = inp_proc[i];

    // Sorting proc
    qsort(proc, number_of_processes, sizeof(process*), &compare);

    // Assigning values for the first process
    proc[0]->starting_time = proc[0]->arrival_time;
    proc[0]->exit_time = proc[0]->arrival_time + proc[0]->burst_time;
    proc[0]->waiting_time = proc[0]->starting_time;

    // Assigning values for other processes
    for (int i = 1; i < number_of_processes; ++i) {
        proc[i]->starting_time = max(proc[i - 1]->exit_time, proc[i]->arrival_time);
        proc[i]->exit_time = proc[i]->starting_time + proc[i]->burst_time;
        proc[i]->waiting_time = proc[i]->starting_time - proc[i]->arrival_time;
    }

    // Generating the output
    printf("P#  AT  BT  CT  TAT  WT\n\n");
    int av_turnaround = 0;
    int av_waiting = 0;
    for (int i = 0; i < number_of_processes; ++i) {
        printf("P%d  %d   %d   %d   %d    %d\n",
               i+1,
               inp_proc[i]->arrival_time,
               inp_proc[i]->burst_time,
               inp_proc[i]->exit_time,
               inp_proc[i]->exit_time - proc[i]->starting_time,
               inp_proc[i]->waiting_time);
        av_turnaround += inp_proc[i]->exit_time - inp_proc[i]->starting_time;
        av_waiting += inp_proc[i]->waiting_time;
    }
    printf("Average turnaround time: %f\nAverage waiting time: %f\n",
           (double)av_turnaround/number_of_processes, (double)av_waiting/number_of_processes);
    return 0;
}