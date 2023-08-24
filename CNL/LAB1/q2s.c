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

// Function to remove duplicate words from the string
void removedups(char strings[][256], char ch[], char res[]) {
    int i, j = 0, k = 0, l;

    // Tokenize the input sentence into words
    for (i = 0; ch[i] != '\0'; i++) {
        if (ch[i] == ' ') {
            strings[j][k] = '\0';
            j++;
            k = 0;
        } else {
            strings[j][k] = ch[i];
            k++;
        }
    }
    strings[j][k] = '\0';

    // Remove duplicate words
    k = 0;
    for (i = 0; i < j; i++) {
        for (l = 1; l < j + 1; l++) {
            if (strings[i][k] == '\0' || l == i) {
                continue;
            }
            if (strcmp(strings[i], strings[l]) == 0) {
                strings[l][k] = '\0';
            }
        }
    }

    // Build the result string without duplicate words
    for (i = 0; i < j + 1; i++) {
        if (strings[i][k] == '\0') {
            continue;
        } else {
            strcat(res, strings[i]);
            strcat(res, " ");
        }
    }
}

int main() {
    int sockfd, newsockfd, portno, clilen, n = 1, i;
    struct sockaddr_in seraddr, cliaddr;

    // Create a socket
    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

    seraddr.sin_family = AF_LOCAL;
    seraddr.sin_addr.s_addr = inet_addr("172.16.59.34"); // Server IP address
    seraddr.sin_port = htons(4003); // Port number

    // Bind the socket
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));

    // Listen for incoming connections
    listen(sockfd, 5);

    while (1) {
        char buf[256] = {""};
        char strings[256][256] = {""};
        char res[256] = {""};
        
        printf("Server Waiting\n");
        clilen = sizeof(cliaddr);

        // Accept a new client connection
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);

        // Read the sentence from the client
        read(newsockfd, buf, sizeof(buf));
        
        // Check if the client wants to stop
        if (strcmp(buf, "Stop") == 0) {
            exit(1); // Terminate the server
        }

        // Remove duplicate words and build the result string
        removedups(strings, buf, res);

        // Send the modified string back to the client
        write(newsockfd, res, sizeof(res));

        // Close the client socket
        close(newsockfd);
    }
}
