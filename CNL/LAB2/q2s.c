/*Implement concurrent Remote Math Server To perform arithmetic operations in the
server and display the result to the client. The client accepts two integers and an
operator from the user and sends it to the server. The server then receives integers and
operator. The server will perform the operation on integers and sends the result back
to the client which is displayed on the client screen. Then both the processes
terminate*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
        if (b != 0)
            result = a / b;
        else
            printf("division by 0 is not possible\n");
        break;
    default:
        printf("invalid operator %c\n", op);
    }
    return result;
}

void handleClient(int client_socket) {
    int a, b, result;
    char op;

    if (read(client_socket, &a, sizeof(a)) < 0) {
        perror("Error reading a");
        close(client_socket);
        return;
    }

    if (read(client_socket, &b, sizeof(b)) < 0) {
        perror("Error reading b");
        close(client_socket);
        return;
    }

    if (read(client_socket, &op, sizeof(op)) < 0) {
        perror("Error reading op");
        close(client_socket);
        return;
    }

    result = performOperation(a, b, op);

    if (write(client_socket, &result, sizeof(result)) < 0) {
        perror("Error writing result");
    }

    close(client_socket);
}

int main() {
    struct sockaddr_in client_addr, server_addr;
    int sock_id, client_socket, client_len;

    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORTNO);
    server_addr.sin_family = AF_INET;

    if (bind(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    if (listen(sock_id, MAX_CLIENTS) < 0) {
        perror("Error listening");
        exit(1);
    }

    client_len = sizeof(client_len);
    client_socket = accept(sock_id, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    if (fork() == 0) {
        close(sock_id);
        handleClient(client_socket);
        exit(1);
    } else {
        close(client_socket);
    }

    return 0;
}
