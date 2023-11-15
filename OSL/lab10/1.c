#include <stdio.h>
#define N_PROCESSES 5
#define N_RESOURCES 3
int max[N_PROCESSES][N_RESOURCES], allocation[N_PROCESSES][N_RESOURCES], need[N_PROCESSES][N_RESOURCES], available[N_RESOURCES];

//pro, res
int isSafe(int need[N_PROCESSES][N_RESOURCES], int available[N_RESOURCES], int n, int m) {
    int work[N_RESOURCES], finish[N_PROCESSES], safeSeq[N_PROCESSES], count = 0;

    for (int i = 0; i < n; i++) finish[i] = 0;
    for (int j = 0; j < m; j++) work[j] = available[j];
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
                        work[k] += allocation[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }if (!found)  return 0;
    }return 1;
}

void handleRequest(int p, int request[N_RESOURCES]) {
    int canGrant = 1;
    for (int j = 0; j < N_RESOURCES; j++) {
        if (request[j] > need[p][j] || request[j] > available[j]) {
            canGrant = 0;
            break;
        }
    }if (canGrant) {
        for (int j = 0; j < N_RESOURCES; j++) {
            allocation[p][j] += request[j];
            available[j] -= request[j];
            need[p][j] -= request[j];
        }
    }
}

void displayMatrix(int matrix[N_PROCESSES][N_RESOURCES], char *name) {
    printf("Updated %s Matrix:\n", name);
    for (int i = 0; i < N_PROCESSES; i++) {
        for (int j = 0; j < N_RESOURCES; j++) {
            printf("%d\t", matrix[i][j]);
        }printf("\n");
    }
}

int main() {
    printf("Enter the Max matrix:\n");
    for (int i = 0; i < N_PROCESSES; i++)
        for (int j = 0; j < N_RESOURCES; j++) scanf("%d", &max[i][j]);

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < N_PROCESSES; i++)
        for (int j = 0; j < N_RESOURCES; j++) scanf("%d", &allocation[i][j]);

    printf("Enter the Available vector:\n");
    for (int j = 0; j < N_RESOURCES; j++) scanf("%d", &available[j]);

    for (int i = 0; i < N_PROCESSES; i++)
        for (int j = 0; j < N_RESOURCES; j++) need[i][j] = max[i][j] - allocation[i][j];

    printf("Content of Need Matrix:\n");
    for (int i = 0; i < N_PROCESSES; i++) {
        for (int j = 0; j < N_RESOURCES; j++) {
            printf("%d\t", need[i][j]);
        }printf("\n");
    }if (isSafe(need, available, N_PROCESSES, N_RESOURCES)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }handleRequest(1, (int[]){1, 0, 2});
    handleRequest(4, (int[]){3, 3, 0});
    handleRequest(0, (int[]){0, 2, 0});
    displayMatrix(allocation, "Allocation");
    displayMatrix(need, "Need");
    printf("Updated Available Vector:\n");
    for (int j = 0; j < N_RESOURCES; j++) {
        printf("%d\t", available[j]);
    }printf("\n");
    if (isSafe(need, available, N_PROCESSES, N_RESOURCES)) {
        printf("The system is in a safe state after handling requests.\n");
    } else {
        printf("The system is not in a safe state after handling requests.\n");
    }return 0;
}