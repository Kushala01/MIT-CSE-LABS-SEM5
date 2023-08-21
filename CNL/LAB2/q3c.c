#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 10300

int main() {
    int sockfd, n;
    struct sockaddr_in servaddr;
    char buf[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation error");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("172.16.59.43"); 
    servaddr.sin_port = htons(PORTNO);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection error");
        exit(1);
    }

    n = read(sockfd, buf, sizeof(buf) - 1);
    if (n < 0) {
        perror("Read error");
        exit(1);
    }
    buf[n] = '\0';

    printf("Received from server: %s\n", buf);

    close(sockfd);

    return 0;
}
