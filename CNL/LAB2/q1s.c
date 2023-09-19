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

#define PORTNO 5656
#define MAX_CLIENTS 5

void sortArray(int arr[], int size){
	int temp;
	for(int i = 0; i < size; i++){
		for(int j = i + 1; j < size; j++){
			if(arr[i]>arr[j]){
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}

void handleClient(int client_socket ){
	int arrSize, proccess_id;
	int arr[100];
	proccess_id=getpid();
	//read(client_socket, &arrSize, sizeof(arrSize));
	recv(client_socket, &arrSize, sizeof(arrSize), 0);
	read(client_socket, arr, sizeof(arr[0])*arrSize);
	sortArray(arr, arrSize);
	write(client_socket, &proccess_id, sizeof(proccess_id));
	write(client_socket, arr, sizeof(arr[0])*arrSize);
	//printf("\n The proccess_id is: %d",proccess_id);
	close(client_socket);
}

void main(){
	int sock_id, client_sock;
	struct sockaddr_in server_addr, client_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORTNO);
	server_addr.sin_addr.s_addr=INADDR_ANY;//accept any connections from any ip address
	int client_len=sizeof(client_addr);

	sock_id=socket(AF_INET, SOCK_STREAM, 0);

	if(bind(sock_id, (struct sockaddr* )&server_addr, sizeof(server_addr))==-1){
		perror("Binding error");
		exit(1);
	}

	if(listen(sock_id, MAX_CLIENTS)==-1){
		printf("listening error");
		exit(1);
	}
	printf("Server is listening....\n");
	while(1){
		if((client_sock=accept(sock_id, (struct sockaddr *)&client_addr, &client_len))==-1){
			printf("client_socket creation error");
			exit(1);
		}
		printf("\nConnection accepted from client");

		if(fork()==0){
			close(sock_id);
			handleClient(client_sock);
			exit(0);
		}else{
			close(client_sock);
		}

	}
}
