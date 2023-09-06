#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define FIFO_NAME "my_fifo"
int main() {
    // Open the FIFO for reading
    int fifoFd = open(FIFO_NAME, O_RDONLY);
    if (fifoFd == -1) {
        perror("Failed to open FIFO for reading");
        exit(EXIT_FAILURE);
    }
    
    // Read data from the FIFO
    char buffer[1024]="lmaoo hahah gtyn";
    ssize_t bytesRead = read(fifoFd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("Error reading from FIFO");
    } else {
        buffer[bytesRead] = '\0';  // Null-terminate the string
        printf("Read from FIFO: %s\n", buffer);
    }
    
    // Close the FIFO file descriptor
    close(fifoFd);
    
    return 0;
}
