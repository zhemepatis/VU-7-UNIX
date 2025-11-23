#include "server.h"

int main()
{
    const char *response = "Hello from TCP Server";
    char buffer[BUFFER_SIZE] = { 0 };
    
    // create socket file descriptor
    int server_socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_desc == 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    // set socket options
    int options = 1;
    if (setsockopt(server_socket_desc, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(options)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in address;
    int addr_len = sizeof(address);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    // bind socket to address + port
    if (bind(server_socket_desc, (struct sockaddr *) &address, sizeof(address)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // mark socket as on ereceiving connections
    if (listen(server_socket_desc, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", SERVER_PORT);

    // accept incoming client connection
    int client_socket = accept(server_socket_desc, (struct sockaddr *) &address, (socklen_t*) &addr_len);
    if (client_socket < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // read data from client
    ssize_t valread = read(client_socket, buffer, BUFFER_SIZE);
    printf("Client message: %s\n", buffer);

    // send response to client
    send(client_socket, response, strlen(response), 0);
    printf("Response sent to client\n");

    // close sockets
    close(client_socket);
    close(server_socket_desc);

    return 0;
}