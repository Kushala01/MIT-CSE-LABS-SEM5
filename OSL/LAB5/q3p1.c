//Write a C program to implement one side of FIFO.

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
#define BUFFER_SIZE 10000       // Define the size of the buffer for data transfer

int main(int argc, char const *argv[])
{
    int pipe_fd, res, open_mode1 = O_WRONLY, open_mode2 = O_RDONLY, n = 0; // Declare variables
    char buffer[BUFFER_SIZE + 1];                  // Declare a buffer for data transfer
    
    // Check if the named pipe (FIFO) exists, create if not
    if (access(FIFO_NAME, F_OK) == -1)
    {
        res = mkfifo(FIFO_NAME, 0777);             // Create FIFO with read/write permissions
        if (res != 0)
        {
            fprintf(stderr, "Could not create files%s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }
    
    printf("Creating a program to communicate with another program through FIFO:\n");
    printf("Currently in Program 1 and starting communication with Program 2...\n");
    
    while (1) // Continuous loop for communication
    {
        pipe_fd = open(FIFO_NAME, open_mode2);     // Open the FIFO for reading
        
        printf("\nText from Program 2: ");
        res = read(pipe_fd, buffer, BUFFER_SIZE);  // Read data from the FIFO
        
        if (strstr(buffer, "exit") != NULL)        // Check for exit command
            break;
        
        printf("%s\n", buffer);                    // Print received text
        close(pipe_fd);                            // Close the FIFO
        
        pipe_fd = open(FIFO_NAME, open_mode1);     // Open the FIFO for writing
        
        printf("Enter the text to send to Program 2: ");
        fgets(buffer, BUFFER_SIZE, stdin);          // Get input from user
        res = write(pipe_fd, buffer, BUFFER_SIZE); // Write data to the FIFO
        
        close(pipe_fd);                            // Close the FIFO
    }
    
    close(pipe_fd);                                // Close the FIFO
    printf("Process %d finished.\n", getpid());    // Print process ID and finished message
    exit(EXIT_SUCCESS);                            // Exit with success status
}
