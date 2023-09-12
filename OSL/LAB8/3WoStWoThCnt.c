/*Write a multithreaded program for generating prime numbers from a given starting
number to the given ending number.*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<stdbool.h>

int start,end;

int isPrime(int n){
	if(n<=1)
		return 0;
	if(n==2)
		return 1;
	for(int i=2;i<n;i++){
		if(n%i==0)
			return 0;
		else
			return 1;
	}
}

void * generatePrime(void * params){
	for(int i=start;i<end;i++){
		if(isPrime(i)){
			printf("%d ",i);
		}
	}
	pthread_exit(0);
}

int main(){
	printf("enter start and end \n");
	scanf("%d %d",&start,&end);

	pthread_t tid;

	if(pthread_create(&tid,0,generatePrime,0)!=0){
		perror("pthread_create");
		return 1;
	}
	if(pthread_join(tid,0)!=0){
		perror("pthread_join");
		return 1;
	}
	return 0;
}
