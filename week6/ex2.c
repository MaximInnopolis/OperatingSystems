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

process* deleteMin(process** array, int size) {
    if (size <= 0)
        return 0;

    int min_i = 0;
    process* min_p = array[min_i];
    for (int i = 1; i < size; i++)
        if (array[i]->burst_time < min_p->burst_time) {
            min_i = i;
            min_p = array[i];
        }

    for (int i = min_i + 1; i < size; ++i)
        array[i-1] = array[i];

    return min_p;
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

    process **queue = malloc(number_of_processes*sizeof(process*));
    int q_size = 0;

    int current_time = 0;
    int done = 0;
    process* current_p;
    while (done < number_of_processes || q_size > 0) {
        while (done < number_of_processes && proc[done]->arrival_time <= current_time)
            queue[q_size++] = proc[done++];
        if (q_size <= 0)
            current_time++;
        else {
            current_p = deleteMin(queue, q_size--);
            current_p->starting_time = current_time;
            current_p->exit_time = current_p->starting_time + current_p->burst_time;
            current_p->waiting_time = current_time - current_p->arrival_time;
            current_time += current_p->burst_time;
        }
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