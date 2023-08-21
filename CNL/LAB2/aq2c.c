#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORTNO 5656

int main() {
    int sock_id, portno, n;
    struct sockaddr_in server_addr;
    char sentence[1024] = {0};

    sock_id = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("172.16.59.43");
    server_addr.sin_port = htons(PORTNO);

    connect(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1) {
        printf("Enter a sentence (or 'Stop' to quit): ");
        fgets(sentence, sizeof(sentence), stdin);
        write(sock_id, sentence, sizeof(sentence));

        if (strcmp(sentence, "Stop\n") == 0) {
            printf("Client stopping...\n");
            break;
        }

        read(sock_id, sentence, sizeof(sentence));
        printf("Received from server: %s\n", sentence);
    }

    close(sock_id);
    return 0;
}
