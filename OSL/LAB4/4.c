/*Write a program to create a new soft link to an existing file and unlink the same.
Accept the old path as input and print the newpath.*/

/* hard links are multiple directory entries that point directly to the same file's inode,
 while symbolic links(soft links) are separate files that point to a target file's pathname.*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char * argv[]){
	if (argc < 2)
    {
        printf("Incorrect number of arguments, Expected 1, Got: %d", argc - 1);
        return 0;
    }

    char * oldpath=argv[1];
    char * newpath="q3.txt";

    struct stat file_stat;

    printf("before linking:\n");
    system("ls");

    int return_value=stat(oldpath,&file_stat);
    if(return_value!=0){
    	perror("stat");
    	return 1;
    }

    printf("\nnumber of links before linking: %ld",file_stat.st_nlink);
    link(oldpath,newpath);
    printf("\nafter linking:\n");
    system("ls");

    int return_value_2 = stat(newpath, &file_stat);
    if (return_value_2 != 0)
    {
        perror("stat");
        return 1;
    }
    printf("\nnumber of links after linking: %ld",file_stat.st_nlink);
    unlink(oldpath);
    printf("After unlinking old link:\n");
    system("ls");
    int return_value_3 = stat(newpath, &file_stat);
    if (return_value_3 != 0)
    {
        perror("stat");
        return 1;
    }
    printf("Number of links after unlinking: %ld\n", file_stat.st_nlink);

    return 0;
}
