#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define N_C 5
#define N_R 3

int avail[N_R];
int max[N_C][N_R];
int alloc[N_C][N_R];
int need[N_C][N_R];

pthread_mutex_t mutex;

int isSafe2(int need[N_C][N_R], int available[N_R], int n, int m) {
    int work[N_C], finish[N_C], safeSeq[N_C], count = 0;

    for (int i = 0; i < n; i++)
        finish[i] = 0;
    for (int j = 0; j < m; j++)
        work[j] = available[j];

    while (1) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            return 0;
        }
    }return 1;
}

bool request(int p, int request[N_R]) {
    int canGrant = 1;
    for (int j = 0; j < N_R; j++) {
        if (request[j] > need[p][j] || request[j] > avail[j]) {
            canGrant = 0;
            break;
        }
    }if (canGrant) {
        for (int j = 0; j < N_R; j++) {
            alloc[p][j] += request[j];
            avail[j] -= request[j];
            need[p][j] -= request[j];
        }return true;
    }else return false;
}

void release(int c, int rel[]) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < N_R; i++) {
        alloc[c][i] -= rel[i];
        need[c][i] += rel[i];
        avail[i] += rel[i];
    }pthread_mutex_unlock(&mutex);
}

void* customerThread(void* arg) {
    int c = *((int*)arg);
    int req[N_R];;

    if (request(1, (int[]){1, 0, 2})) {
        printf("C%d req granted.\n", c);
        release(c, req);
        printf("C%d released resources.\n", c);
    } else {
        printf("C%d req denied.\n", c);
    }pthread_exit(NULL);
}

void displayMatrix(int matrix[N_C][N_R], char *name) {
    printf("Updated %s Matrix:\n", name);
    for (int i = 0; i < N_C; i++) {
        for (int j = 0; j < N_R; j++) {
            printf("%d\t", matrix[i][j]);
        }printf("\n");
    }
}

int main() {
    pthread_t threads[N_C];
    int c_args[N_C];

    printf("Enter the Max matrix:\n");
    for (int i = 0; i < N_C; i++)
        for (int j = 0; j < N_R; j++) scanf("%d", &max[i][j]);

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < N_C; i++)
        for (int j = 0; j < N_R; j++) scanf("%d", &alloc[i][j]);

    printf("Enter the Available vector:\n");
    for (int j = 0; j < N_R; j++) scanf("%d", &avail[j]);

    for (int i = 0; i < N_C; i++)
        for (int j = 0; j < N_R; j++) need[i][j] = max[i][j] - alloc[i][j];

    printf("Content of Need Matrix:\n");
    for (int i = 0; i < N_C; i++) {
        for (int j = 0; j < N_R; j++) {
            printf("%d\t", need[i][j]);
        }printf("\n");
    }if (isSafe2(need, avail, N_C, N_R)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }
    displayMatrix(alloc, "Allocation");
    displayMatrix(need, "Need");
    printf("Updated Available Vector:\n");
    for (int j = 0; j < N_R; j++) {
        printf("%d\t", avail[j]);
    }printf("\n");

    
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N_C; i++) {
        c_args[i] = i;
        pthread_create(&threads[i], NULL, customerThread, &c_args[i]);
    }for (int i = 0; i < N_C; i++) 
        pthread_join(threads[i], NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}