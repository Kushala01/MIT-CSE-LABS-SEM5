/*Write a TCP concurrent client server program where server accepts integer array from
client and sorts it and returns it to the client along with process id.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

#define PORTNO 5656

void main(){
	int sock_id;
	struct sockaddr_in address;
	int arr_size, proccess_id;
	int arr[100];

	sock_id=socket(AF_INET, SOCK_STREAM, 0);
	if(sock_id==-1){
		printf("Coonection error");
		exit(1);
	}
	
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_family=AF_INET;
	address.sin_port=htons(PORTNO);
	if(connect(sock_id,(struct sockaddr*)&address, sizeof(address))==-1){
		printf("\nconnection error");
		exit(1);
	}
	printf("\n enter the array size ");
	scanf("%d",&arr_size);
	printf("\nenter the elements present in the array ");
	for(int i=0;i<arr_size;i++){
		scanf("%d",&arr[i]);
	}
	write(sock_id, &arr_size, sizeof(arr_size));
	write(sock_id, arr, sizeof(arr[0])*arr_size);

	read(sock_id, &proccess_id, sizeof(proccess_id));
	printf("\nSorted array from the server with pid %d is :\n ",proccess_id);
	read(sock_id, arr, sizeof(arr[0])*arr_size);
	for(int i=0;i<arr_size;i++){
		printf(" %d ",arr[i]);
	}
	printf("\n");
	close(sock_id);

}
