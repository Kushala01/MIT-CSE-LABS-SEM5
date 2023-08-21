#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 5656
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

void removeDuplicates(char *sentence) {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount = 0;

    char *word = strtok(sentence, " ");
    while (word != NULL && wordCount < MAX_WORDS) {
        int duplicate = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(words[i], word) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            strcpy(words[wordCount], word);
            wordCount++;
        }
        word = strtok(NULL, " ");
    }

    sentence[0] = '\0';
    for (int i = 0; i < wordCount; i++) {
        strcat(sentence, words[i]);
        strcat(sentence, " ");
    }
}

int main() {
    int sock_id, new_sockid, portno, client_len;
    struct sockaddr_in server_addr, client_addr;

    sock_id = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORTNO);

    bind(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sock_id, 5);

    while (1) {
        char sentence[1024] = {0};
        client_len = sizeof(client_addr);
        new_sockid = accept(sock_id, (struct sockaddr *)&client_addr, &client_len);

        printf("Client connected\n");
        
        while (1) {
            read(new_sockid, sentence, sizeof(sentence));
            if (strcmp(sentence, "Stop\n") == 0) {
                printf("Stopping server...\n");
                break;
            }
            
            printf("Received from client: %s\n", sentence);
            
            removeDuplicates(sentence);
            write(new_sockid, sentence, sizeof(sentence));
        }

        close(new_sockid);
    }

    close(sock_id);
    return 0;
}
