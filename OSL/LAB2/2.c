#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void printFiles(char* dir)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    dp=opendir(dir);
    if(!dp)
    {
        printf("Cannot open directory : %s\n",dir);
        exit(0);
    }
    chdir(dir);//It changes the current working directory to the specified directory 
    //using chdir so that relative paths can be used for the recursive calls.
    while(entry=readdir(dp))
    {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))
        {
            if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
            {
                continue;
            }
            printf("%s\n",entry->d_name);
            printf("\n");
            printFiles(entry->d_name);
        }
        else
        {
            printf("%s\n",entry->d_name);
        }
    }
    printf("\n");
    chdir("..");//After processing all entries in the current directory, it prints a 
    //newline and changes the working directory back to the parent directory using chdir("..").
}

void main()
{
    char dir[256];
    printf("Enter Directory Name : \t");
    scanf("%s",dir);
    printFiles(dir);
}