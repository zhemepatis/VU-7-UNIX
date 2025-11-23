#include "client.h"

int main()
{
    // create socket file descriptor
    int server_socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_desc < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    // set socket options
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    // connect to the server
    if (connect(server_socket_desc, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // send message to server
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from TCP Client";

    send(server_socket_desc, message, strlen(message), 0);
    printf("Message sent to server\n");

    // receive message from server
    ssize_t valread = read(server_socket_desc, buffer, BUFFER_SIZE);
    printf("Server response: %s\n", buffer);

    // close socket
    close(server_socket_desc);

    return 0;
}