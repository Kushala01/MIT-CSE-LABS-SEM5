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
    int open_mode = O_RDONLY;
    char buffer[BUFFER_SIZE + 1];
    memset(buffer, '\0', sizeof(buffer));

    printf("Consumer opening FIFO O_RDONLY\n");
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Consumer result %d\n", pipe_fd);

    if (pipe_fd != -1) {
        int shelfCount = 0;
        printf("Consumer: Starting to remove items from the shelf\n");

        while (1) {
            if (shelfCount > 0) {
                shelfCount--;
                snprintf(buffer, BUFFER_SIZE, "Item removed from shelf. Current shelf count: %d\n", shelfCount);
                printf("%s", buffer);
            } else {
                snprintf(buffer, BUFFER_SIZE, "No items on the shelf.\n");
                printf("%s", buffer);
            }

            res = read(pipe_fd, buffer, BUFFER_SIZE);  // Read from the producer (not used)
            usleep(1000000);  // Sleep for 1 second
        }

        (void)close(pipe_fd);
    } else
        exit(EXIT_FAILURE);

    printf("Consumer Finished\n");
    exit(EXIT_SUCCESS);
}
