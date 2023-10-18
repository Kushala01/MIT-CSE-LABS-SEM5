#include <stdio.h>
#include <stdlib.h>

// Process structure
struct Process {
    int id;              // Process ID
    int burst_time;      // Total burst time required for the process
    int remaining_time;  // Remaining burst time for the process
    int queue_level;     // Queue level for the process in MLFQ
};
typedef struct Process Process;

// Function to execute a process for a given time quantum
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
    // Create a set of processes (you can initialize them as needed)
    Process processes[5];
    for (int i = 0; i < 5; i++) {
        processes[i].id = i;
        processes[i].burst_time = (i + 1) * 10; // Burst time for each process (e.g., 10, 20, 30, 40, 50)
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].queue_level = 0; // All processes start at the top queue
    }

    // Define time quantum for each queue
    int time_quantums[3] = {10, 20, 40}; // Time quantums for each queue (e.g., 10, 20, 40)

    // Simulate the MLFQ
    int current_time = 0;
    int quantum_index = 0;

    while (1) {
        int quantum = time_quantums[quantum_index];
        int found = 0;
        
        // Execute processes in the current queue
        for (int i = 0; i < 5; i++) {
            if (processes[i].remaining_time > 0 && processes[i].queue_level == quantum_index) {
                found = 1;
                current_time += executeProcess(&processes[i], quantum);

                // Demote the process to the next queue if it didn't finish
                if (processes[i].remaining_time > 0 && quantum_index < 2) {
                    processes[i].queue_level++;
                }
            }
        }

        // Check if we need to move to the next queue
        if (found == 0) {
            quantum_index = (quantum_index + 1) % 3;
            if (quantum_index == 0) {
                // Check if all processes are completed
                int all_completed = 1;
                for (int i = 0; i < 5; i++) {
                    if (processes[i].remaining_time > 0) {
                        all_completed = 0;
                        break;
                    }
                }
                if (all_completed) {
                    break; // All processes completed
                }
            }
        }
    }

    return 0;
}