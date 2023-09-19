/*Implement concurrent Remote Math Server To perform arithmetic operations in the
server and display the result to the client. The client accepts two integers and an
operator from the user and sends it to the server. The server then receives integers and
operator. The server will perform the operation on integers and sends the result back
to the client which is displayed on the client screen. Then both the processes
terminate.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#define PORTNO 5656
#define MAX_CLIENTS 5

void main(){
	int sock_id,a ,b,result,addr_len;
	char op;
	struct sockaddr_in address;

	sock_id=socket(AF_INET, SOCK_STREAM, 0);

	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(PORTNO);
	address.sin_family=AF_INET;

	//	addr_len=sizeof(addr_len);
	if (connect(sock_id, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("Connection error");
        exit(1);
    }

	printf("enter a and b: \n");
	scanf("%d %d",&a,&b);
	printf("\nEnter operator (+, -, *, /): ");
	scanf(" %c", &op);  // Notice the space before %c to consume any previous newline character.


	write(sock_id, &a, sizeof(a));
	write(sock_id, &b, sizeof(b));
	write(sock_id, &op, sizeof(char));

	read(sock_id, &result, sizeof(result));
	printf("\n result is : %d\n",result);

	close(sock_id);
}
