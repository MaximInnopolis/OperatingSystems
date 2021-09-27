#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int starting_time;
    int exit_time;
    int waiting_time;
    int remaining_time;
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

void delete(process** array, int index, int size) {
    if (size <= 0)
        return;
    for (int i = index + 1; i < size; i++) {
        array[i - 1] = array[i];
    }
}

int main() {
    process **inp_proc; // Contain processes in the order of their entering
    process **proc; // Contain processes in sorted order (by arrival time)
    int number_of_processes;
    int quantum;

    printf("Enter the number of processes:\n");
    scanf("%d", &number_of_processes);

    printf("Enter the size of quantum:\n");
    scanf("%d", &quantum);

    // Initializing inp_proc and proc
    proc = malloc(number_of_processes * sizeof(process*));
    inp_proc = malloc(number_of_processes * sizeof(process*));
    for (int i = 0; i < number_of_processes; ++i) {
        inp_proc[i] = malloc(sizeof(process));
    }

    // Requiring input
    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < number_of_processes; ++i) {
        printf("Enter the arrival time of process %d:\n", i+1);
        scanf("%d", &(inp_proc[i]->arrival_time));
        printf("Enter the burst time of process %d:\n", i+1);
        scanf("%d", &(inp_proc[i]->burst_time));
        inp_proc[i]->remaining_time = inp_proc[i]->burst_time;
        inp_proc[i]->id = i;
    }

    // Copying inp_proc to proc
    for (int i = 0; i < number_of_processes; ++i) {
        proc[i] = inp_proc[i];
    }

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
            for (int i = 0; i < q_size; i++) {
                if (queue[i]->remaining_time == queue[i]->burst_time) {
                    queue[i]->starting_time = current_time;
                    queue[i]->waiting_time = current_time - queue[i]->arrival_time;
                }
                if (queue[i]->remaining_time <= quantum) {
                    current_time += queue[i]->remaining_time;
                    queue[i]->exit_time = current_time;
                    delete(queue, i, q_size--);
                    i--;
                } else {
                    queue[i]->remaining_time -= quantum;
                    current_time += quantum;
                }
                while (done < number_of_processes && proc[done]->arrival_time <= current_time)
                    queue[q_size++] = proc[done++];
            }
        }
    }

    // Generating the output
    printf("P#  AT  BT  CT  TAT  WT\n\n");
    int av_turnaround = 0;
    int av_waiting = 0;
    for (int i = 0; i < number_of_processes; ++i) {
        int turnaround = inp_proc[i]->exit_time - inp_proc[i]->starting_time;
        inp_proc[i]->waiting_time += turnaround - inp_proc[i]->burst_time;

        printf("P%d  %d   %d   %d   %d    %d\n",
               i+1,
               inp_proc[i]->arrival_time,
               inp_proc[i]->burst_time,
               inp_proc[i]->exit_time,
               inp_proc[i]->exit_time - proc[i]->starting_time,
               inp_proc[i]->waiting_time);
        av_turnaround += turnaround;
        av_waiting += inp_proc[i]->waiting_time;
    }
    printf("Average turnaround time: %f\nAverage waiting time: %f\n",
           (double)av_turnaround/number_of_processes, (double)av_waiting/number_of_processes);
    return 0;
}