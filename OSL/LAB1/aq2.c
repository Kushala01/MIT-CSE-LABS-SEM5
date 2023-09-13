/*Use lseek() to copy different parts (initial, middle and last) of the file to others. (For
lseek() refer to man pages)*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int source_fd, initial_fd, middle_fd, last_fd;
    ssize_t nread;
    char buffer[BUFFER_SIZE];

    // Open the source file for reading
    source_fd = open("source.txt", O_RDONLY);
    if (source_fd == -1) {
        perror("open");
        return 1;
    }

    // Create destination files
    initial_fd = open("initial.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    middle_fd = open("middle.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    last_fd = open("last.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (initial_fd == -1 || middle_fd == -1 || last_fd == -1) {
        perror("open");
        return 1;
    }

    // Set the file offset to the beginning
    lseek(source_fd, 0, SEEK_SET);

    // Copy the initial part (first 100 bytes)
    nread = read(source_fd, buffer, 100);
    write(initial_fd, buffer, nread);

    // Set the file offset to the middle (e.g., 500 bytes from the beginning)
    lseek(source_fd, 500, SEEK_SET);

    // Copy the middle part (next 200 bytes)
    nread = read(source_fd, buffer, 200);
    write(middle_fd, buffer, nread);

    // Set the file offset to the end (e.g., 100 bytes before the end)
    lseek(source_fd, -100, SEEK_END);

    // Copy the last part (last 100 bytes)
    nread = read(source_fd, buffer, 100);
    write(last_fd, buffer, nread);

    // Close the files
    close(source_fd);
    close(initial_fd);
    close(middle_fd);
    close(last_fd);

    return 0;
}
