// Interface.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

struct shm_area {
    int status;
    char msg[128];
};

int main() {
    int shmid = shmget((key_t)1234, sizeof(struct shm_area), 0666 | IPC_CREAT);
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
    shm_ptr->status = 0;

    while(1) {
        while(shm_ptr->status == 1) {
            sleep(1);  // Waiting for display to clear the memory
        }

        printf("Enter your message: ");
        fgets(shm_ptr->msg, 128, stdin);
        shm_ptr->status = 1;
    }

    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}