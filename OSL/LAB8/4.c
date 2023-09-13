/*Write a multithreaded program that performs the sum of even numbers and odd
numbers in an input array. Create a separate thread to perform the sum of even
numbers and odd numbers. The parent thread has to wait until both the threads are
done.*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<stdint.h>
#define MAX_SIZE 100

int arr[MAX_SIZE];

void * computeOddSum(void * size){
	int n=*((int *)size);
	int oddSum=0;
	for(int i=0;i<n;i++){
		if(i%2!=0){
		oddSum+=arr[i];	
		}
	}
	pthread_exit((void *)(intptr_t)oddSum);
}
void * computeEvenSum(void * size){
	int n=*((int *)size);
	int evenSum=0;
	for(int i=0;i<n;i++){
		if(i%2==0){
		evenSum+=arr[i];	
		}
	}
	pthread_exit((void *)(intptr_t)evenSum);
}

int main(){
	int size,resultOdd,resultEven;
	printf("enter the size of the array \n");
	scanf("%d",&size);

	printf("enter the elements of the array \n");
	for(int i=0;i<size;i++){
		scanf("%d",&arr[i]);
	}

	pthread_t odd,even;

	int thread_args=size;

	if(pthread_create(&odd,0,computeOddSum,&thread_args)!=0){
		perror("pthread_create");
		return 1;
	}
	if(pthread_create(&even,0,computeEvenSum,&thread_args)!=0){
		perror("pthread_create");
		return 1;
	}
	if(pthread_join(odd,(void **)&resultOdd)!=0){
		perror("pthread_join");
		return 1;
	}
		if(pthread_join(even,(void **)&resultEven)!=0){
		perror("pthread_join");
		return 1;
	}
	printf("\nthe odd and even resulst are %d %d\n",resultOdd,resultEven);
	return 0;
}
