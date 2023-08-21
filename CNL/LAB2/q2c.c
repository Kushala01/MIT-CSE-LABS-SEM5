#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTNO 5656

int main() {
    int sock_id;
    struct sockaddr_in server_addr;
    int a, b, result;
    char op;

    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id == -1) {
        perror("Socket creation error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNO);
    server_addr.sin_addr.s_addr = inet_addr("172.16.59.43"); 

    if (connect(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection error");
        exit(1);
    }

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &op);

    send(sock_id, &a, sizeof(a), 0);
    send(sock_id, &b, sizeof(b), 0);
    send(sock_id, &op, sizeof(op), 0);

    recv(sock_id, &result, sizeof(result), 0);
    printf("Result received from server: %d\n", result);

    close(sock_id);

    return 0;
}
