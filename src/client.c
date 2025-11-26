#include "client.h"

int main()
{
    // create socket file descriptor
    int server_socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_desc < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // set socket to non-blocking mode
    int flags = fcntl(server_socket_desc, F_GETFL, 0);
    fcntl(server_socket_desc, F_SETFL, flags | O_NONBLOCK);
    
    // set socket options
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_ADDRESS, &server_address.sin_addr) <= 0)
    {
        perror("invalid address");
        
        // close socket
        close(server_socket_desc);
        
        exit(EXIT_FAILURE);
    }

    // connect to the server
    int connect_result = connect(server_socket_desc, (struct sockaddr *) &server_address, sizeof(server_address));
    
    if (connect_result < 0)
    {
        // check if there were any actual errors on connection
        if (errno != EINPROGRESS)
        {
            perror("connect");
            
            close(server_socket_desc);

            exit(EXIT_FAILURE);
        }

        // wait for connection
        struct pollfd pfd;
        pfd.fd = server_socket_desc;
        pfd.events = POLLOUT;

        connect_result = poll(&pfd, 1, 5000);

        // check if poll was successful
        if (connect_result <= 0)
        {
            perror("poll");
            
            close(server_socket_desc);

            exit(EXIT_FAILURE);
        }
    }

    printf("Connected to [%s] on port [%d]\n", SERVER_ADDRESS, SERVER_PORT);

    // start connection processing
    printf("Connection processing started\n");
    processConnection(server_socket_desc);

    // close connection processing
    close(server_socket_desc);
    printf("Connection processing finished\n");

    return 0;
}

void processConnection(int server_socket_desc)
{
    printf("Processing connection... \n");

    // send message to server
    // char buffer[BUFFER_SIZE] = {0};
    // const char *message = "Hello from TCP Client";

    // send(server_socket_desc, message, strlen(message), 0);
    // printf("Message sent to server\n");

    // // receive message from server
    // ssize_t valread = read(server_socket_desc, buffer, BUFFER_SIZE);
    // printf("Server response: %s\n", buffer);
}

