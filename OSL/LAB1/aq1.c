/*Write a program that shows the user all his/her C source programs and then prompts
interactively as to whether others should be granted read permission; if affirmative
such permission should be granted.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    char directory_path[256]; // Stores the path of the directory to search
    struct dirent *entry;
    struct stat file_stat;
    DIR *dir;

    // Prompt the user for the directory path
    printf("Enter the directory path: ");
    scanf("%s", directory_path);

    // Open the directory
    dir = opendir(directory_path);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // List all C source code files in the directory
    printf("C source code files in %s:\n", directory_path);
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c") != NULL) {
            printf("- %s\n", entry->d_name);

            // Ask the user if they want to grant read permission
            char response;
            printf("Grant read permission for this file? (y/n): ");
            scanf(" %c", &response);

            if (response == 'y' || response == 'Y') {
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s/%s", directory_path, entry->d_name);
                if (stat(filepath, &file_stat) == 0) {
                    // Add read permission for the file's owner
                    chmod(filepath, file_stat.st_mode | S_IRUSR);
                    printf("Read permission granted for %s\n", entry->d_name);
                }
            }
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
