#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 100

int main() {
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    char buffer[BUFFER_SIZE + 1];

    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create file %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }

    printf("Producer opening FIFO O_WRONLY\n");
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Producer result %d\n", pipe_fd);

    if (pipe_fd != -1) {
        int shelfCount = 0;
        printf("Producer: Starting to stock items on the shelf\n");

        while (1) {
            if (shelfCount < 5) {
                shelfCount++;
                snprintf(buffer, BUFFER_SIZE, "Item added to shelf. Current shelf count: %d\n", shelfCount);
                res = write(pipe_fd, buffer, BUFFER_SIZE);
                if (res == -1) {
                    fprintf(stderr, "Write Error on Pipe\n");
                    exit(EXIT_FAILURE);
                }
                printf("%s", buffer);
            }
            usleep(500000);  // Sleep for 500 ms
        }

        (void)close(pipe_fd);
    } else
        exit(EXIT_FAILURE);

    printf("Producer Finished\n");
    exit(EXIT_SUCCESS);
}
