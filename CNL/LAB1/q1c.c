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
	int sock_id, portno, client_len, new_sockid, n=1;
	struct sockaddr_in server_addr, client_addr;

	sock_id=socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORTNO);

	bind(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr));
	listen(sock_id,5);

		char buf[256]="";
		printf("\n....Server Waiting......");
		client_len=sizeof(client_len);
		new_sockid=accept(sock_id, (struct sockaddr*)&client_addr, &client_len);

		n=read(new_sockid, buf, sizeof(buf));
		printf("\nEncypted message from the client is: %s",buf);
		for(int i=0;i<strlen(buf);i++){
			buf[i]-=4;
		}
		printf("\n Decrypted message from client is : %s\n",buf);
		close(new_sockid);
}
