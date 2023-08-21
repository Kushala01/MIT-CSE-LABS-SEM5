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
    int arr_size, process_id;
    int arr[100]; // Assuming a maximum of 100 integers in the array

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

    // Input array size and elements
    printf("Enter the size of the array: ");
    scanf("%d", &arr_size);

    printf("Enter the array elements:\n");
    for (int i = 0; i < arr_size; i++) {
        scanf("%d", &arr[i]);
    }

    // Send array size and data to server
    send(sock_id, &arr_size, sizeof(arr_size), 0);
    send(sock_id, arr, sizeof(arr[0]) * arr_size, 0);

    // Receive sorted array and process ID from server
    recv(sock_id, &process_id, sizeof(process_id), 0);
    recv(sock_id, arr, sizeof(arr[0]) * arr_size, 0);

    printf("Sorted Array received from server (Process ID %d):\n", process_id);
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    close(sock_id);

    return 0;
}
