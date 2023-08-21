#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTNO 5656
#define MAX_CLIENTS 5

int performOperation(int a, int b, char op) {
    int result = 0;
    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b != 0) {
                result = a / b;
            } else {
                printf("Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Invalid operator.\n");
    }
    return result;
}

void handleClient(int client_socket) {
    int a, b, result;
    char op;

    recv(client_socket, &a, sizeof(a), 0);
    recv(client_socket, &b, sizeof(b), 0);
    recv(client_socket, &op, sizeof(op), 0);

    result = performOperation(a, b, op);
    send(client_socket, &result, sizeof(result), 0);

    close(client_socket);
}

int main() {
    int sock_id, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id == -1) {
        perror("Socket creation error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNO);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding error");
        exit(1);
    }

    if (listen(sock_id, MAX_CLIENTS) == -1) {
        perror("Listening error");
        exit(1);
    }

    printf("Server is listening...\n");

    while (1) {
        client_sock = accept(sock_id, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock == -1) {
            perror("Accepting error");
            exit(1);
        }
        printf("Connection accepted from a client\n");

        if (fork() == 0) {
            close(sock_id); // Child process doesn't need the listening socket
            handleClient(client_sock);
            exit(0);
        } else {
            close(client_sock); // Parent process doesn't need this client socket
        }
    }

    return 0;
}
