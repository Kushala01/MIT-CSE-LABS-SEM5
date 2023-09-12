/*Write a program to create a new hard link to an existing file and unlink the same.
Accept the old path as input and print the newpath.*/

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

/*    The program starts by checking if the correct number of command-line arguments is provided. 
		If not, it displays an error message.

    The oldpath is extracted from the command-line arguments, which represents the path to the existing file.

    A newpath is defined to specify the name of the new hard link that will be created.

    The program displays the list of files before creating the new link using the system("ls"); command.

    The program uses the stat function to get information about the existing file before creating the link.
    It then displays the current number of links to the file.

    The program creates a new hard link using the link function, linking the oldpath to the newpath.

    The program displays the list of files again after creating the new link.

    It retrieves information about the new link using stat and displays the number of links after linking along with the newpath.

    The program unlinks the oldpath using the unlink function to remove the original link to the file.

    The list of files is displayed once more after unlinking the old link.

    Information about the new link is retrieved again using stat, and the program displays the updated number of links after unlinking.*/
