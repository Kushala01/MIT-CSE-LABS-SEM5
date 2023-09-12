/*Write a multithreaded program that calculates the summation of non-negative
integers in a separate thread and passes the result to the main thread.*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdint.h>

void* calculateSum(void * arg){
	int n=*((int *)arg);
	int sum=0;
	for(int i=0;i<n;i++){
		sum+=i;
	}
	pthread_exit((void *)(intptr_t)sum);
}

int main(char argc,char * argv[]){
	if(argc!=2){
		printf("u didnt enter the number: ");
		return 1;
	}
	int n=atoi(argv[1]);
	pthread_t tid;
	int thread_arg=n;

	if(pthread_create(&tid,0,calculateSum,&thread_arg)!=0){
		perror("pthread_create");
		return 1;
	}
	int result;

	if(pthread_join(tid,(void **)&result)!=0){
		perror("pthread_join");
		return 1;
	}
	printf("\nthe ans is : %d \n",result);
	return 0;
}
/*int main() {
    int n;

    // Prompt the user for input
    printf("Enter a non-negative integer (up to 30): ");
    scanf("%d", &n);

    if (n < 0 || n > 30) {
        printf("Please enter a non-negative integer up to 30.\n");
        return 1;
    }*/
