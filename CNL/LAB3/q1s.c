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
    int sd, m ,n, len;
    struct sockaddr_in server_addr, client_addr;

    sd=socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORTNO);

    len=sizeof(client_addr);
    bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    recvfrom(sd, &m, sizeof(m), 0,(struct sockaddr *)&client_addr, &len);
    recvfrom(sd, &n, sizeof(n), 0,(struct sockaddr *)&client_addr, &len);

    int arr[m][n];
    int revarr[n];
    int rowCount=0;

    while(rowCount<m){
        recvfrom(sd, revarr, n*sizeof(int), 0, (struct sockaddr *)&client_addr, &len);
        for(int i=0;i<n;i++){
            arr[rowCount][i]=revarr[i];
        }
        rowCount++;
    }
    printf("After combining the matrix is: \n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }   
}
