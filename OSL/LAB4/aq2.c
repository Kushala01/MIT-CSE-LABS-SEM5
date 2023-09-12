//Write a program to print the full stat structure of a directory.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    const char *dirname = argv[1];
    struct stat dir_stat;

    if (stat(dirname, &dir_stat) == -1) {
        perror("stat");
        return 1;
    }

    printf("Statistics for Directory: %s\n", dirname);
    printf("Inode: %ld\n", dir_stat.st_ino);
    printf("Size: %ld bytes\n", dir_stat.st_size);
    printf("Number of hard links: %ld\n", dir_stat.st_nlink);
    printf("User ID of owner: %d\n", dir_stat.st_uid);
    printf("Group ID of owner: %d\n", dir_stat.st_gid);
    printf("Device ID: %ld\n", dir_stat.st_dev);
    printf("Block size for filesystem I/O: %ld\n", dir_stat.st_blksize);
    printf("Number of blocks allocated: %ld\n", dir_stat.st_blocks);
    printf("Last access time: %ld\n", dir_stat.st_atime);
    printf("Last modification time: %ld\n", dir_stat.st_mtime);
    printf("Last status change time: %ld\n", dir_stat.st_ctime);

    return 0;
}
