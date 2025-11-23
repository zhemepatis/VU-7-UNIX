#include "client.h"

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from TCP Client";

    // Step 1: Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);

    // Convert IPv4 address from text to binary (e.g., "127.0.0.1" -> binary)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    // Step 2: Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Send message to server
    send(sock, message, strlen(message), 0);
    printf("Message sent to server\n");

    // Receive response from server
    ssize_t valread = read(sock, buffer, BUFFER_SIZE);
    printf("Server response: %s\n", buffer);

    // Step 4: Close socket
    close(sock);
    return 0;
}