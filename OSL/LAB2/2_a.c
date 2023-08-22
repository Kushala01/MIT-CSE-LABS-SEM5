/*Write a program that allows the user to remove any or all of the files in a current
working directory. The name of the file should appear followed by a prompt as to
whether it should be removed.*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Function to prompt user to remove files in the directory
void printFiles(char* dir) {
    DIR *dp; // Directory stream pointer
    struct dirent *entry; // Pointer to directory entry
    struct stat statbuf; // Structure to store file status information
    dp = opendir(dir);

    if (!dp) {
        printf("Cannot open directory : %s\n", dir);
        exit(0);
    }
    chdir(dir); // Change the working directory to the specified directory
    char c;

    // Loop through directory entries
    while ((entry = readdir(dp))) {
        lstat(entry->d_name, &statbuf);
        if (!S_ISDIR(statbuf.st_mode)) { // Check if it's a file (not a directory)
            printf("Do you want to remove the file (Y|N) : %s\n", entry->d_name);
            scanf(" %c", &c); // Get user input (Y or N)

            if (c == 'Y' || c == 'y') {
                remove(entry->d_name); // Remove the file if user confirms
            }
        }
    }
    closedir(dp); // Close the directory
    chdir(".."); // Change the working directory back to the parent directory
}

void main() {
    char dir[256];
    printf("Enter Directory Name : \t");
    scanf("%s", dir);

    // Call the printFiles function to start removing files
    printFiles(dir);
}
