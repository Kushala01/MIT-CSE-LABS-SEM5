/*Write a program to find the inode number of all files in a directory. Take the input as
a directory name and print the inode numbers of all the files in it.*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include<string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    const char *dirname = argv[1];
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dirname);

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Ignore . and .. special entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path of the file
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);

        struct stat file_stat;
        if (stat(filepath, &file_stat) == 0) {
            if (S_ISREG(file_stat.st_mode)) {
                printf("File: %s, Inode: %ld\n", filepath, file_stat.st_ino);
            }
        }
    }

    closedir(dir);
    return 0;
}
