//Write a concurrent TCP daytime server ‘C’ program. Along with the result, server
//should also send the process id to the client.

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
	int sockid, pid;
	struct sockaddr_in address;
	char tt[256];

	sockid=socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family=AF_INET;
	address.sin_port=htons(PORTNO);
	address.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(sockid, (struct sockaddr *)&address, sizeof(address));

	read(sockid, &pid, sizeof(pid));
	read(sockid, tt, sizeof(tt));

	printf("\n pid : %d \n time : %s\n",pid,tt);
}
