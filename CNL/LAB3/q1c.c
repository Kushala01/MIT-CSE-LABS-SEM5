/*Write a UDP client-server program where t he client sends rows of a matrix, and the
server combines them together as a matrix.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<time.h>

#define PORTNO 5656
#define MAX_CLIENTS 5

void main(){
	int sd;
	struct sockaddr_in address;
	sd=socket(AF_INET, SOCK_DGRAM, 0);
	address.sin_family=AF_INET;
	address.sin_port=htons(PORTNO);
	address.sin_addr.s_addr=inet_addr("127.0.0.1");

	int m, n;
	int len=sizeof(address);

	printf("Enter the number of Rows :");
	scanf("%d",&m);
	sendto(sd, &m, sizeof(m), 0, (struct sockaddr *)&address, len);

	printf("Enter the number of Columns :");
	scanf("%d",&n);
	sendto(sd, &n, sizeof(n), 0, (struct sockaddr *)&address, len);

	int arr[n];
	int rowCount=0;

	printf("Enter the Elements :");
	while(rowCount<m){
		for(int i=0;i<n;i++){
			scanf("%d",&arr[i]);
		}
		sendto(sd, arr, n*sizeof(int), 0, (struct sockaddr *)&address, len);
		rowCount++;
	}
}
