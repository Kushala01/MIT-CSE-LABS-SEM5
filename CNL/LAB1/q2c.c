/*Where the client accepts a sentence from the user and sends it to the server. The server
will check for duplicate words in the string. Server will find number of occurrences of
duplicate words present and remove the duplicate words by retaining single occurrence of
the word and send the resultant sentence to the client. The client displays the received
data on the client screen. The process repeats until the user enter the string “Stop”. Then
both the processes terminate.*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#define PORTNO 4545

void main(){
	int len, result, sock_id, n=1;
	struct sockaddr_in address;
	char ch[256],buf[256];

	sock_id=socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(PORTNO);

	len=sizeof(address);
	result=connect(sock_id, (struct sockaddr_in*)&address, len);
	if(result == -1){
		printf("\n client error..");
		exit(1);
	}

	printf("Enter of the String: \n");
	gets(ch);
	ch[strlen(ch)]='\0';

	if(strcmp(ch,"Stop")==0){
		close(sock_id);
		//sbreak;
	}
	write(sock_id, ch, strlen(ch));
	read(sock_id, buf, sizeof(buf));

	printf("\n string after removing dups : ");
	puts(buf);

	close(sock_id);
}
