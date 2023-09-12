/* Write a program to find the inode number of an existing file in a directory. Take the
input as a filename and print the inode number of the file. */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char const* argv[]){
	if(argc <2){
		printf("didnt enter the inp file");
		perror("enter filename");
		return 1;
	}

	struct stat ans;

	int returnVal=stat(argv[1],&ans);

	if(returnVal!=0){
		perror("stat");
		return 1;
	}

	printf("\ninode %ld and filename %s\n",ans.st_ino,argv[1]);
	return 0;
}
