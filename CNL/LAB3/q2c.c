/*Write a client program to send a manually crafted HTTP request packet to a Web Server
and display all fields received in HTTP Response at client Side.*/ 
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

int main()
{
	int sd;
	struct sockaddr_in address;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("172.16.59.51");
	address.sin_port=htons(PORTNO);
	char buf[256];
	int len=sizeof(address);
	//'GET /index.html HTTP/1.1\r\nHost:stackoverflow.com\r\n\r\n'
	printf("Enter the request: ");
	scanf("%[^\n]",buf);
	sendto(sd,buf,sizeof(buf),0,(struct sockaddr *)&address, len);

	return 0;
}
