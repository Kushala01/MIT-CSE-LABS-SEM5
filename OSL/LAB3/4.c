/*Create a zombie (defunct) child process (a child with exit() call, but no
corresponding wait() in the sleeping parent) and allow the init process to adopt it
(after parent terminates). Run the process as a background process and run the “ps”
command.*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int status; // Variable to store the status of the child process
    pid_t pid = fork(); // Create a child process
    
    if(pid < 0){ // Forking failed
        printf("\nError Occurred");
        exit(-1); // Exit with an error status
    }
    else if(pid == 0){ // Child process
        exit(0); // Exit the child process
    }
    else{ // Parent process
        sleep(10000); // Sleep for a long time to create a zombie process
    }
    
    return 0; // Exit the program
}
