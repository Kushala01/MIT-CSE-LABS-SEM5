#include <stdio.h>

// Define constants for the maximum number of processes and resources
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3
int max[MAX_PROCESSES][MAX_RESOURCES]; // Max demand matrix
int allocation[MAX_PROCESSES][MAX_RESOURCES]; // Allocation matrix
int need[MAX_PROCESSES][MAX_RESOURCES]; // Need matrix
int available[MAX_RESOURCES]; // Available vector

// Function to check if a state is safe
int isSafe(int need[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES], int n, int m) {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];

    // Initialize work vector with available resources
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    // Initialize finish array
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int safeSequence[MAX_PROCESSES];
    int count = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m) {
                    // Process i can be safely executed
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            // If no process can be executed, the system is not in a safe state
            return 0;
        }
    }

    // If all processes can be executed, the system is in a safe state
    return 1;
}

int main() {
    
    printf("Enter the Max matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Available vector:\n");
    for (int j = 0; j < MAX_RESOURCES; j++) {
        scanf("%d", &available[j]);
    }

    // Calculate the Need matrix
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    printf("Content of Need Matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d\t",need[i][j]);
        }
        printf("\n");
    }
    // Check if the system is in a safe state
    if (isSafe(need, available, MAX_PROCESSES, MAX_RESOURCES)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    // Handle request scenarios and update matrices as needed
    // (c) Request from P1 for (1, 0, 2)
    // Implement this scenario, check if it can be granted and update matrices

    // (d) Request from P4 for (3, 3, 0)
    // Implement this scenario, check if it can be granted and update matrices

    // (e) Request from P0 for (0, 2, 0)
    // Implement this scenario, check if it can be granted and update matrices
     int requestP1[MAX_RESOURCES] = {1, 0, 2};
    int p1 = 1;  // Process P1
    int canGrantP1 = 1;  // Assume the request can be granted

    for (int j = 0; j < MAX_RESOURCES; j++) {
        if (requestP1[j] > need[p1][j] || requestP1[j] > available[j]) {
            canGrantP1 = 0;  // The request cannot be granted
            break;
        }
    }

    if (canGrantP1) {
        // Grant the request to P1
        for (int j = 0; j < MAX_RESOURCES; j++) {
            allocation[p1][j] += requestP1[j];
            available[j] -= requestP1[j];
            need[p1][j] -= requestP1[j];
        }
    }

    // (d) Request from P4 for (3, 3, 0)
    int requestP4[MAX_RESOURCES] = {3, 3, 0};
    int p4 = 4;  // Process P4
    int canGrantP4 = 1;  // Assume the request can be granted

    for (int j = 0; j < MAX_RESOURCES; j++) {
        if (requestP4[j] > need[p4][j] || requestP4[j] > available[j]) {
            canGrantP4 = 0;  // The request cannot be granted
            break;
        }
    }

    if (canGrantP4) {
        // Grant the request to P4
        for (int j = 0; j < MAX_RESOURCES; j++) {
            allocation[p4][j] += requestP4[j];
            available[j] -= requestP4[j];
            need[p4][j] -= requestP4[j];
        }
    }

    // (e) Request from P0 for (0, 2, 0)
    int requestP0[MAX_RESOURCES] = {0, 2, 0};
    int p0 = 0;  // Process P0
    int canGrantP0 = 1;  // Assume the request can be granted

    for (int j = 0; j < MAX_RESOURCES; j++) {
        if (requestP0[j] > need[p0][j] || requestP0[j] > available[j]) {
            canGrantP0 = 0;  // The request cannot be granted
            break;
        }
    }

    if (canGrantP0) {
        // Grant the request to P0
        for (int j = 0; j < MAX_RESOURCES; j++) {
            allocation[p0][j] += requestP0[j];
            available[j] -= requestP0[j];
            need[p0][j] -= requestP0[j];
        }
    }

    // Display the updated Allocation matrix
printf("Updated Allocation Matrix:\n");
for (int i = 0; i < MAX_PROCESSES; i++) {
    for (int j = 0; j < MAX_RESOURCES; j++) {
        printf("%d\t", allocation[i][j]);
    }
    printf("\n");
}

// Display the updated Need matrix
printf("Updated Need Matrix:\n");
for (int i = 0; i < MAX_PROCESSES; i++) {
    for (int j = 0; j < MAX_RESOURCES; j++) {
        printf("%d\t", need[i][j]);
    }
    printf("\n");
}

// Display the updated Available vector
printf("Updated Available Vector:\n");
for (int j = 0; j < MAX_RESOURCES; j++) {
    printf("%d\t", available[j]);
}
printf("\n");


    // Check if the system is still in a safe state after handling requests
    if (isSafe(need, available, MAX_PROCESSES, MAX_RESOURCES)) {
        printf("The system is in a safe state after handling requests.\n");
    } else {
        printf("The system is not in a safe state after handling requests.\n");
    }

    return 0;
}