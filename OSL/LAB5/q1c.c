/*Write a producer and consumer program in C using the FIFO queue. The producer
should write a set of 4 integers into the FIFO queue and the consumer should
display the 4 integers.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int pipe_fd, res, open_mode = O_RDONLY, n = 0;  // Declare variables
    char buffer[BUFFER_SIZE + 1];                   // Declare a buffer for data transfer
    memset(buffer, '\0', sizeof(buffer));           // Clear the buffer
    
    printf("Process %d opening FIFO O_RDONLY\n", getpid());  // Print process ID
    
    pipe_fd = open(FIFO_NAME, open_mode);          // Open the named pipe for reading
    int bytes_read = 0;                            // Variable to track bytes read
    
    if (pipe_fd != -1)                            // Check if opening the FIFO succeeded
    {
        do
        {
            printf("%d : ", n + 1);
            
            // Read data from the named pipe into the buffer
            res = read(pipe_fd, buffer, BUFFER_SIZE);
            printf("%s\n", buffer);               // Print the read data
            
            bytes_read += res;                     // Update bytes_read count
            n++;                                   // Increment the counter
        } while (n < 4);                           // Repeat for 4 iterations
        
        close(pipe_fd);                            // Close the named pipe after reading
    }
    else
    {
        exit(EXIT_FAILURE);                        // Exit if opening FIFO fails
    }
    
    printf("Process %d finished, %d bytes read.\n", getpid(), bytes_read);  // Print process ID and bytes read
    exit(EXIT_SUCCESS);                            // Exit with success status
    return 0;                                      // Return 0 as program completion indicator
}
