//Demonstrate creation, writing to, and reading from a pipe.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    int n, fd[2];                         // Declare variables for pipe file descriptors
    char buf[1025], *data = "Sample Data for my OS Lab";  // Declare a buffer and sample data
    
    pipe(fd);                             // Create a pipe with file descriptors fd[0] and fd[1]
    write(fd[1], data, strlen(data));     // Write data into the write end of the pipe
    n = read(fd[0], buf, 1024);           // Read data from the read end of the pipe
    
    if (n >= 0)                           // Check if reading was successful
    {
        buf[n] = 0;                       // Null-terminate the read data to make it a string
        printf("Read %d bytes from the pipe\n\"%s\"\n", n, buf);  // Print the read data
    }
    else
        perror("Read");                   // Print an error message if reading failed
    
    exit(0);                              // Exit with success status
}