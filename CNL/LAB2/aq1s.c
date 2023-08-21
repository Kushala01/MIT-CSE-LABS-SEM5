#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define PORTNO 10400

void handleClient(int newsockfd) {
    char buf[256];
    time_t now;
    struct tm *timeinfo;
    pid_t pid = getpid();
    char pid_str[16];

    time(&now);
    timeinfo = localtime(&now);
    strftime(buf, sizeof(buf), "Server time: %Y-%m-%d %H:%M:%S", timeinfo);
    sprintf(pid_str, "PID: %d", pid);
    strcat(buf, "\n");
    strcat(buf, pid_str);

    write(newsockfd, buf, strlen(buf));
    close(newsockfd);
    exit(0);
}

int main() {
    int sockfd, newsockfd, clilen;
    struct sockaddr_in seraddr, cliaddr;

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

    printf("Server is listening on port %d...\n", PORTNO);

    while (1) {
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        if (newsockfd < 0) {
            perror("Accept error");
            exit(1);
        }

        pid_t child_pid = fork();
        if (child_pid < 0) {
            perror("Fork error");
            exit(1);
        } else if (child_pid == 0) {
            // Child process handles client
            close(sockfd); // Close listening socket in child
            handleClient(newsockfd);
        } else {
            // Parent process continues listening
            close(newsockfd); // Close new socket in parent
        }
    }

    return 0;
}
