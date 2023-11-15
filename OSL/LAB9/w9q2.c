#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int queue_level;
};
typedef struct Process Process;

int executeProcess(Process *process, int time_quantum) {
    if (process->remaining_time <= time_quantum) {
        printf("Process %d executed for %d units. Completed.\n", process->id, process->remaining_time);
        process->remaining_time = 0;
        return process->remaining_time;
    } else {
        printf("Process %d executed for %d units. Remaining time: %d\n", process->id, time_quantum, process->remaining_time - time_quantum);
        process->remaining_time -= time_quantum;
        return time_quantum;
    }
}

int main() {
    Process processes[5];
    for (int i = 0; i < 5; i++) {
        processes[i].id = i;
        processes[i].burst_time = (i + 1) * 10;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].queue_level = 0; // All processes start at the top queue
    }int time_quantums[3] = {10, 20, 40}; 
    int current_time = 0;
    int quantum_index = 0;
    while (1) {
        int quantum = time_quantums[quantum_index];
        int found = 0;   
        for (int i = 0; i < 5; i++) {
            if (processes[i].remaining_time > 0 && processes[i].queue_level == quantum_index) {
                found = 1;
                current_time += executeProcess(&processes[i], quantum);
                if (processes[i].remaining_time > 0 && quantum_index < 2) {
                    processes[i].queue_level++;
                }
            }
        }if (found == 0) {
            quantum_index = (quantum_index + 1) % 3;
            if (quantum_index == 0) {
                int all_completed = 1;
                for (int i = 0; i < 5; i++) {
                    if (processes[i].remaining_time > 0) {
                        all_completed = 0;
                        break;
                    }
                }if (all_completed)   break;
            }
        }
    }return 0;
}