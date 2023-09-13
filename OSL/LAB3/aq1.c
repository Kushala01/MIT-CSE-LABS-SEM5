//orphan process
 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // This is the child process.
        printf("Child process PID: %d\n", getpid());
        printf("Parent of child (before parent exit) PID: %d\n", getppid());

        // Sleep for a few seconds to delay termination.
        sleep(5);

        printf("Parent of child (after parent exit) PID: %d\n", getppid());
    } else {
        // This is the parent process.
        printf("Parent process PID: %d\n", getpid());
        // Sleep for a short time before exiting.
        sleep(2);
    }

    return 0;
}
