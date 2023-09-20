/*Write a concurrent TCP daytime server ‘C’ program. Along with the result, server
should also send the process id to the client.*/

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

void handleClient(int newsockid){
    printf("created a new child with pid : %d\n",getpid());
    time_t t;
    time(&t);
    char tt[256];
    strcpy(tt, ctime(&t));
    int pid=getpid();
    write(newsockid, &pid, sizeof(pid));
    write(newsockid, tt, sizeof(tt));
    close(newsockid);
    //exit(0);
}
void main(){
    int sockid, newsockid, clilen, n=1;
    int size;
    struct sockaddr_in client_addr, server_addr;
    sockid=socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_port=htons(PORTNO);
    bind(sockid, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(sockid, 5);

   while(1){
        clilen=sizeof(clilen);
        newsockid=accept(sockid, (struct sockaddr *)&client_addr, &clilen);

        if(fork() == 0){
            close(sockid);
            handleClient(newsockid);
            exit(0);
        }else{
            close(newsockid);
        }
    }
}
