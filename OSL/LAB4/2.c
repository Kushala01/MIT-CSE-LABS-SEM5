/*WAP to print out the complete stat structure of a file.*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>// For struct stat and stat function
#include <sys/types.h>// For data types like ino_t
#include <time.h> // For ctime() function

// Function to convert permission mode to string
const char *perms(__mode_t mode)
{
    static char buf[16] = {0};    // Initialize a character buffer to store permission characters
	int i = 0;    // Initialize an index variable

	// Set permission characters based on user permissions
	buf[i++] = ((mode & S_IRUSR) ? 'r' : '-');    // Check if user has read permission
	buf[i++] = ((mode & S_IWUSR) ? 'w' : '-');    // Check if user has write permission
	buf[i++] = ((mode & S_IXUSR) ? 'x' : '-');    // Check if user has execute permission

	// Set permission characters based on group permissions
	buf[i++] = ((mode & S_IRGRP) ? 'r' : '-');    // Check if group has read permission
	buf[i++] = ((mode & S_IWGRP) ? 'w' : '-');    // Check if group has write permission
	buf[i++] = ((mode & S_IXGRP) ? 'x' : '-');    // Check if group has execute permission

	// Set permission characters based on other permissions
	buf[i++] = ((mode & S_IROTH) ? 'r' : '-');    // Check if others have read permission
	buf[i++] = ((mode & S_IWOTH) ? 'w' : '-');    // Check if others have write permission
	buf[i++] = ((mode & S_IXOTH) ? 'x' : '-');    // Check if others have execute permission

    return buf;
}


int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Incorrect number of arguments, Expected 1, Got: %d", argc - 1);
        return 0;
    }
    // Declare a struct to store file statistics
    struct stat file_stat;
    // Use the stat function to get file statistics
    int return_value = stat(argv[1], &file_stat);
    if (return_value != 0)
    {
        perror("stat");
        return 1;
    }
   // Print out the complete stat structure information
	printf("File: %s\n", argv[1]);    // Print the filename
	printf("Inode: %ld\n", file_stat.st_ino);    // Print the inode number
	printf("Device Container ID: %ld\n", file_stat.st_dev);    // Print the device container ID
	printf("Mode: %10.10s\n", perms(file_stat.st_mode));    // Print the file mode (permissions)
	printf("Hard Links: %ld\n", file_stat.st_nlink);    // Print the number of hard links
	printf("User ID: %d\n", file_stat.st_uid);    // Print the user ID of the owner
	printf("Group ID: %d\n", file_stat.st_gid);    // Print the group ID of the owner
	printf("Device ID: %ld\n", file_stat.st_rdev);    // Print the device ID
	printf("Total Size: %ld\n", file_stat.st_size);    // Print the total size in bytes
	printf("Block Size: %ld\n", file_stat.st_blksize);    // Print the block size for filesystem I/O
	printf("Number of blocks: %ld\n", file_stat.st_blocks);    // Print the number of blocks allocated
	printf("Last Access Time: %s\n", ctime(&file_stat.st_atime));    // Print the last access time
	printf("Last Modified: %s\n", ctime(&file_stat.st_mtime));    // Print the last modification time
	printf("Last Status: %s", ctime(&file_stat.st_ctime));    // Print the last status change time

    return 0;
}