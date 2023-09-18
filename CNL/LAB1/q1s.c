/*To illustrate encryption and decryption of messages using TCP. The client accepts
messages to be encrypted through standard input device. The client will encrypt the string
by adding 4(random value) to ASCII value of each alphabet. The encrypted message is
sent to the server. The server then decrypts the message and displays both encrypted and
decrypted forms of the string. Program terminates after one session.*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define PORTNO 4546

void main(){
	int len, result, sock_id, n=1;
	struct sockaddr_in address;
	char ch[256];

	sock_id=socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(PORTNO);
	len=sizeof(address);

	result=connect(sock_id, &address, len);

	if(result== -1){
		perror("\n client error\n");
		exit(1);
	}

	printf("enter string : ");
	gets(ch);

	ch[strlen(ch)]='\0';

	for(int i=0;i<strlen(ch);i++){
		ch[i]+=4;
	}
	write(sock_id, ch, strlen(ch));
}
