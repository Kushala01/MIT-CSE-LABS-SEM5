#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define PORTNO 10300
#define MAX_CLIENTS 5

void printCurrentTime() {
    time_t now;
    struct tm *timeinfo;
    char buffer[80];
    time(&now);
    timeinfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("[%s] ", buffer);
}

int main() {
    int sockfd, newsockfd, portno, clilen, n;
    char buf[256];
    struct sockaddr_in seraddr, cliaddr;
    fd_set readfds;
    int client_sockets[MAX_CLIENTS] = {0}; // Array to store client socket descriptors

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation error");
        exit(1);
    }

    memset(&seraddr, 0, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_port = htons(PORTNO);

    if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("Binding error");
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror("Listen error");
        exit(1);
    }

    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    printf("Server is listening on port %d...\n", PORTNO);

    while (1) {
        fd_set temp_fds = readfds;
        if (select(FD_SETSIZE, &temp_fds, NULL, NULL, NULL) < 0) {
            perror("Select error");
            exit(1);
        }

        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &temp_fds)) {
                if (i == sockfd) {
                    // New client connection
                    clilen = sizeof(cliaddr);
                    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
                    if (newsockfd < 0) {
                        perror("Accept error");
                        exit(1);
                    }
                    FD_SET(newsockfd, &readfds);
                    printCurrentTime();
                    printf("New client connected\n");
                } else {
                    // Data from existing client
                    n = read(i, buf, sizeof(buf));
                    if (n <= 0) {
                        if (n == 0) {
                            printCurrentTime();
                            printf("Client disconnected\n");
                        } else {
                            perror("Read error");
                        }
                        close(i);
                        FD_CLR(i, &readfds);
                    } else {
                        // Respond with the current time
                        time_t now;
                        struct tm *timeinfo;
                        time(&now);
                        timeinfo = localtime(&now);
                        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
                        write(i, buf, strlen(buf));
                        printCurrentTime();
                        printf("Sent time to client: %s\n", buf);
                    }
                }
            }
        }
    }

    return 0;
}
