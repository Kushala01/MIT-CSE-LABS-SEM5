/*Write a C program to emulate the ls -l UNIX command that prints all files in a
current directory and lists access privileges, etc. DO NOT simply exec ls -l from the
program.*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void main()
{
    char dir[256];//directory name
    printf("Enter Directory Name : \t");
    scanf("%s",dir);
    DIR *dp;//open dir
    struct dirent *entry;//Declares a pointer to a struct dirent (entry) to hold directory entry information.
    struct stat statbuf;//Declares a struct stat (statbuf) to store file status information.
    dp=opendir(dir);//Opens the directory specified by the dir variable using opendir.
    if(!dp)//Checks if the directory couldn't be opened (!dp), and if so, prints an error message, then exits the program.
    {
        fprintf(stderr,"Cannot open directory : %s\n",dir);
        exit(0);
    }
    while(entry=readdir(dp))
    {
        lstat(entry->d_name,&statbuf);
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
        {
            continue;
        }
        /*
- Enters a loop that iterates through each directory entry using `readdir`.
- For each entry, it retrieves file status information using `lstat`.
- Checks if the entry is either `.` (current directory) or `..` (parent directory).
- If it's one of these special entries, it skips the rest of the loop iteration using `continue`.*/


        printf("%s\t\t\t",entry->d_name);
        if(S_ISDIR(statbuf.st_mode))
        {
            printf(S_ISDIR(statbuf.st_mode)  ? "d" : "-");
        }
        printf(statbuf.st_mode & S_IRUSR ? "r" : "-");
        printf(statbuf.st_mode & S_IWUSR ? "w" : "-");
        printf(statbuf.st_mode & S_IXUSR ? "x" : "-");
        printf(statbuf.st_mode & S_IRGRP ? "r" : "-");
        printf(statbuf.st_mode & S_IWGRP ? "w" : "-");
        printf(statbuf.st_mode & S_IXGRP ? "x" : "-");
        printf(statbuf.st_mode & S_IROTH ? "r" : "-");
        printf(statbuf.st_mode & S_IWOTH ? "w" : "-");
        printf(statbuf.st_mode & S_IXOTH ? "x" : "-");
        printf("\n");
    }
    closedir(dp);
}
