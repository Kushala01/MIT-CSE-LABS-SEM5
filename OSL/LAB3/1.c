/*Write a program to find the inode number of an existing file in a directory. Take the
input as a filename and print the inode number of the file.*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	printf("starting parent process ");
	int return_value=fork();

	switch(return_value){
	case -1:{
		perror("fork");
		return 1;
	}
	case 0:{
		printf("in child process");
		for(int i=0;i<10;i++){
			sleep(1);
			printf("\nsleeping child\n");
		}
		exit(0);
	}
	break;
	default:{
		printf("inside parent waiting");
		wait(0);
		//wait(NULL);
		printf("[*] Child process finished execution\n");
		exit(0);
	}
	}
}
