/*Where the client accepts a sentence from the user and sends it to the server. The server
will check for duplicate words in the string. Server will find number of occurrences of
duplicate words present and remove the duplicate words by retaining single occurrence of
the word and send the resultant sentence to the client. The client displays the received
data on the client screen. The process repeats until the user enter the string “Stop”. Then
both the processes terminate.*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#define PORTNO 4545

void removedups(char strings[][256], char ch[], char res[]){
	int i,j=0,k=0,l;

	for(i=0; ch[i]!='\0'; i++){
		if (ch[i]==' '){
			strings[j][k]='\0';
			j++;
			k=0;
		}else{
			strings[j][k]=ch[i];
			k++;
		}
	}
	strings[j][k]='\0';
	k=0;
	for(i = 0; i < j; i++){
		for( l = 1; l < j+1; l++){
			if(strings[i][k]=='\0' || i == l){
				continue;
			}
			if(strcmp(strings[i],strings[l])==0){
				strings[l][k]='\0';
			}
		}
	}
	for( i = 0; i <= j; i++){
		if(strings[i][k]=='\0'){
			continue;
		}
		strcat(res, strings[i]);
		strcat(res, " ");
	}
}

int main(){
	int sock_id,new_sockid,portno,client_len,n=1;
	struct sockaddr_in client_addr, server_addr;

	sock_id = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORTNO);

	bind(sock_id, (struct sockaddr*)&server_addr, sizeof(server_addr));

	listen(sock_id, 5);

	while(1){
		char buf[256]={""};
		char strings[256][256]={""};
		char res[256]={""};

		printf(".....Server Waiting.......\n");
		client_len=sizeof(client_len);

		new_sockid=accept(sock_id, (struct sockaddr*)&client_addr, &client_len);
		read(new_sockid, buf, sizeof(buf));

		printf("Message recieved from client : \n");
		puts(buf);
		if(strcmp(buf,"Stop")==0){
			exit(1);
		}

		removedups(strings, buf, res);

		write(new_sockid, res, sizeof(res));
		close(new_sockid);
	}
}
