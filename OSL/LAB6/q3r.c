// Display.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

struct shm_area {
    int status;
    char msg[128];
};

int main() {
    int shmid = shmget((key_t)1234, sizeof(struct shm_area), 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    void *shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    struct shm_area *shm_ptr = (struct shm_area *)shared_memory;

    while(1) {
        if (shm_ptr->status == 1) {
            printf("Received message: %s", shm_ptr->msg);
            shm_ptr->status = 0;  // Clear the memory
        }
    }

    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}