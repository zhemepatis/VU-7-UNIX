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
    char buffer[BUFFER_SIZE] = { 0 };
    int buffer_length;

    // send greetings command
    strcpy(buffer, "greet-me");
    buffer_length = strlen(buffer);
    
    logMessage("SERVER", buffer);
    ssize_t send_result = send(server_socket_desc, buffer, BUFFER_SIZE, 0);
    memset(buffer, 0, BUFFER_SIZE);
    
    // receive greetings
    ssize_t recv_result = recv(server_socket_desc, buffer, BUFFER_SIZE, 0);
    logMessage("SERVER", buffer);
    memset(buffer, 0, BUFFER_SIZE);
    
    // send exit command
    strcpy(buffer, "exit");
    buffer_length = strlen(buffer);

    logMessage("SERVER", buffer);
    send_result = send(server_socket_desc, buffer, BUFFER_SIZE, 0);
}