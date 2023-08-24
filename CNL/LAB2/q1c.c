/*Write a TCP concurrent client server program where server accepts integer array from
client and sorts it and returns it to the client along with process id.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTNO 5656

int main() {
    int sock_id; // Socket descriptor
    struct sockaddr_in server_addr; // Address structure for server
    int arr_size, process_id; // Variables to store array size and process ID
    int arr[100]; // Assuming a maximum of 100 integers in the array

    // Create a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id == -1) {
        perror("Socket creation error");
        exit(1);
    }

    // Set up server address details
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNO); // Port number
    server_addr.sin_addr.s_addr = inet_addr("172.16.59.43"); // Server IP address

    // Connect to the server
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

    // Send array size and data to the server
    send(sock_id, &arr_size, sizeof(arr_size), 0);
    send(sock_id, arr, sizeof(arr[0]) * arr_size, 0);

    // Receive sorted array and process ID from the server
    recv(sock_id, &process_id, sizeof(process_id), 0);
    recv(sock_id, arr, sizeof(arr[0]) * arr_size, 0);

    // Display the received sorted array and process ID
    printf("Sorted Array received from server (Process ID %d):\n", process_id);
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Close the socket
    close(sock_id);

    return 0;
}
