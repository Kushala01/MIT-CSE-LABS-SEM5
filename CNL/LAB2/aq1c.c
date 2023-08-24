//Write a concurrent TCP daytime server ‘C’ program. Along with the result, server
//should also send the process id to the client.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10400

int main() {
    int sockfd, n;
    struct sockaddr_in servaddr;
    char buf[256];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation error");
        exit(1);
    }

    // Set up server address details
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("172.16.59.43"); // Server IP address
    servaddr.sin_port = htons(PORTNO); // Port number

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection error");
        exit(1);
    }

    // Read data from the server
    n = read(sockfd, buf, sizeof(buf) - 1);
    if (n < 0) {
        perror("Read error");
        exit(1);
    }
    buf[n] = '\0';

    // Print the received message from the server
    printf("Received from server:\n%s\n", buf);

    // Close the socket
    close(sockfd);

    return 0;
}
