/*Write a program to create a new soft link to an existing file and unlink the same.
Accept the old path as input and print the newpath.*/

/* hard links are multiple directory entries that point directly to the same file's inode,
 while symbolic links(soft links) are separate files that point to a target file's pathname.*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Incorrect number of arguments, Expected 1, Got: %d", argc - 1);
        return 0;
    }

    // Get the old path from command-line argument
    char *oldpath = argv[1];

    // Define the new path for the new symbolic link
    char *newpath = "q4-new.txt";

    // Structure to store file information
    struct stat file_stat;

    // Display current files before linking
    printf("Before linking new link:\n");
    system("ls");

    // Get information about the file before linking
    int return_value = stat(oldpath, &file_stat);
    if (return_value != 0)
    {
        perror("stat");
        return 1;
    }

    // Display the number of links before linking
    printf("Number of links before linking: %ld\n", file_stat.st_nlink);

    // Create a new symbolic link
    symlink(oldpath, newpath);

    // Display current files after linking
    printf("After linking new link:\n");
    system("ls");

    // Get information about the new link
    int return_value_2 = stat(newpath, &file_stat);
    if (return_value_2 != 0)
    {
        perror("stat");
        return 1;
    }

    // Display the number of links after linking and the new path
    printf("Number of links after linking: %ld\nThe new path is: %s\n", file_stat.st_nlink, newpath);

    // Unlink the new symbolic link
    unlink(newpath);

    // Display current files after unlinking
    printf("After unlinking new soft link:\n");
    system("ls");

    // Get information about the old file after unlinking
    int return_value_3 = stat(oldpath, &file_stat);
    if (return_value_3 != 0)
    {
        perror("stat");
        return 1;
    }

    // Display the number of links after unlinking
    printf("Number of links after unlinking: %ld\n", file_stat.st_nlink);

    return 0;
}
