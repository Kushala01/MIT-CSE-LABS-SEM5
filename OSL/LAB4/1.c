/* Write a program to find the inode number of an existing file in a directory. Take the
input as a filename and print the inode number of the file. */

#include <unistd.h>      // For the stat system call
#include <stdio.h>       // For standard I/O functions
#include <stdlib.h>      // For exit()
#include <sys/stat.h>    // For struct stat and stat function
#include <sys/types.h>   // For data types like ino_t

int main(int argc, char const *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc < 2) {
        printf("Incorrect number of arguments. Expected 1, Got: %d\n", argc - 1);
        return 0;
    }
    
    // Declare a struct to store file stat
    struct stat file_stat;
    
    // Use the stat function to get file statistics
    int return_value = stat(argv[1], &file_stat);
    
    // Check for any errors in the stat function
    if (return_value != 0) {
        perror("stat");   // Print the error message
        return 1;         
    }
    
    // Print the filename and its associated inode number
    printf("File: %s ---- Inode: %ld\n", argv[1], file_stat.st_ino);
    
    return 0;   
}
