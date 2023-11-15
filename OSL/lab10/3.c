#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

struct DSA {
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
};

void FCFS(struct DSA* dsa, int n) {
    int current_position = 0;
    int total_seek_time = 0;

    printf("FCFS Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        printf("Move from %d to %d\n", current_position, dsa[i].cylinder);
        total_seek_time += abs(current_position - dsa[i].cylinder);
        current_position = dsa[i].cylinder;
    }printf("Total Seek Time: %d\n", total_seek_time);
}

void SSTF(struct DSA* dsa, int n) {
    int current_position = 0;
    int total_seek_time = 0;
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("SSTF Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        int min_seek = INT_MAX;
        int next_request = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int seek = abs(current_position - dsa[j].cylinder);
                if (seek < min_seek) {
                    min_seek = seek;
                    next_request = j;
                }
            }
        }if (next_request != -1) {
            visited[next_request] = 1;
            printf("Move from %d to %d\n", current_position, dsa[next_request].cylinder);
            total_seek_time += min_seek;
            current_position = dsa[next_request].cylinder;
        }
    }printf("Total Seek Time: %d\n", total_seek_time);
}

int main() {
    struct DSA dsa[] = {
        {1, 0, 40, 0, 1},
        {2, 0, 35, 0, 2},
        {3, 0, 10, 0, 3},
        {4, 0, 90, 0, 4},
        {5, 0, 5, 0, 5}
    };
    int n = sizeof(dsa) / sizeof(dsa[0]);
    FCFS(dsa, n);
    printf("\n");
    SSTF(dsa, n);
    return 0;
}