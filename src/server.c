#include "server.h"

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "Hello from TCP Server";

    // Step 1: Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to reuse port/address (avoids "address in use" errors)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    address.sin_port = htons(SERVER_PORT); // Convert port to network byte order (big-endian)

    // Step 2: Bind socket to address/port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Listen for incoming connections (backlog=3: max pending connections)
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("TCP Server listening on port %d...\n", SERVER_PORT);

    // Step 4: Accept incoming connection (blocks until client connects)
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Step 5: Read data from client
    ssize_t valread = read(new_socket, buffer, BUFFER_SIZE);
    printf("Client message: %s\n", buffer);

    // Send response to client
    send(new_socket, response, strlen(response), 0);
    printf("Response sent to client\n");

    // Step 6: Close sockets
    close(new_socket);
    close(server_fd);
    return 0;
}