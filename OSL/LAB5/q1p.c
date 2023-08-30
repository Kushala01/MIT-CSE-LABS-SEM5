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

#define FIFO_NAME "my_queue"    // Define the name of the FIFO (Named Pipe)
#define BUFFER_SIZE 1000        // Define the size of the buffer for data transfer

int main(int argc, char *argv[])
{
    int pipe_fd, res, open_mode = O_WRONLY, n = 0;   // Declare variables
    char buffer[BUFFER_SIZE + 1];                   // Declare a buffer for data transfer
    
    // Check if the named pipe (FIFO) exists, create if not
    if (access(FIFO_NAME, F_OK) == -1)
    {
        // Create the named pipe with appropriate permissions
        res = mkfifo(FIFO_NAME, 0777);               // Create FIFO with read/write permissions
        if (res != 0)
        {
            fprintf(stderr, "Could not create file %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);                      // Exit if FIFO creation fails
        }
    }
    
    printf("Process %d opening FIFO O_WRONLY\n", getpid()); // Print process ID
    
    // Open the named pipe for writing
    pipe_fd = open(FIFO_NAME, open_mode);           // Open the FIFO for writing
    
    if (pipe_fd != -1)                             // Check if opening the FIFO succeeded
    {
        printf("Enter 4 numbers: \n");
        while (n < 4)                               // Loop to input 4 integers
        {
            printf("%d : ", n + 1);
            
            // Read input from user and store it in the buffer
            scanf("%s", buffer);
            
            // Write data from the buffer into the named pipe
            res = write(pipe_fd, buffer, BUFFER_SIZE); // Write data to the FIFO
            
            if (res == -1)
            {
                fprintf(stderr, "Write error on PIPE\n");
                exit(EXIT_FAILURE);                  // Exit if write error occurs
            }
            n++;
        }
        
        close(pipe_fd);                             // Close the named pipe after writing
    }
    else
    {
        exit(EXIT_FAILURE);                         // Exit if opening FIFO fails
    }
    
    printf("Process %d finished\n", getpid());       // Print process ID
    
    exit(EXIT_SUCCESS);                             // Exit with success status
    return 0;                                       // Return 0 as program completion indicator
}
