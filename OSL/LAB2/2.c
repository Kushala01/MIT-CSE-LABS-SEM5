/*Write a program that will list all files in a current directory and all files in
subsequent subdirectories.*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Function to print files in the current directory and its subdirectories
void printFiles(char* dir) {
    DIR *dp; // Directory stream pointer
    struct dirent *entry; // Pointer to directory entry
    struct stat statbuf; // Structure to store file status information

    // Open the specified directory using opendir
    dp = opendir(dir);
    if (!dp) {
        printf("Cannot open directory : %s\n", dir);
        exit(0);
    }

    // Change the working directory to the specified directory
    chdir(dir);

    // Loop through directory entries
    while (entry = readdir(dp)) {
        lstat(entry->d_name, &statbuf);

        // Check if the entry is a directory
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue; // Skip "." and ".." entries
            }
            printf("%s\n", entry->d_name); // Print directory name
            printf("\n");

            // Recursively call printFiles function for the subdirectory
            printFiles(entry->d_name);
        } else {
            printf("%s\n", entry->d_name); // Print file name
        }
    }

    printf("\n");

    // Change the working directory back to the parent directory
    chdir("..");
}

void main() {
    char dir[256];
    printf("Enter Directory Name : \t");
    scanf("%s", dir);

    // Call the printFiles function to start listing files
    printFiles(dir);
}
