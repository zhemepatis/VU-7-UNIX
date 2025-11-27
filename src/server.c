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

    // bind socket to specified address and port
    int bind_result = bind(server_socket_desc, (struct sockaddr *) &address, sizeof(address));
    if (bind_result < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // set socket to non-blocking mode
    int flags = fcntl(server_socket_desc, F_GETFL, 0);
    fcntl(server_socket_desc, F_SETFL, flags | O_NONBLOCK);

    // mark socket as receiving connections
    int listen_result = listen(server_socket_desc, MAX_CONNECTIONS_ALLOWED);
    if (listen_result < 0)
    {
        perror("listen");
        close(server_socket_desc);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", SERVER_PORT);

    while (true)
    {
        // accept incoming client connection
        int client_socket = accept(server_socket_desc, (struct sockaddr *) &address, (socklen_t*) &addr_len);

        if (client_socket < 0)
        {
            // wait for connection
            if (errno == EAGAIN)
            {
                struct pollfd polled_desc;
                polled_desc.fd = server_socket_desc;
                polled_desc.events = POLLIN;

                int poll_result = poll(&polled_desc, 1, -1);
                continue;
            }

            perror("accept");
            break;
        }

        int fork_result = fork();
        
        // check if fork was successful
        if (fork_result < 0)
        {
            perror("fork");
            close(client_socket);
            close(server_socket_desc);
            exit(EXIT_FAILURE);
        }

        // check if it's child process
        if (fork_result == 0)
        {
            // start connection processing
            printf("Connection processing started\n");
            processConnection(client_socket);
            printf("Connection processing finished\n");

            break;
        }
    }

    // close server socket
    close(server_socket_desc);

    return 0;
}

void processConnection(int client_socket_desc)
{
    char buffer[BUFFER_SIZE];

    while (true)
    {
        readInfo(client_socket_desc, buffer);

        Command command = parseCommand(buffer);

        if (command == EXIT)
        {
            break;
        }

        executeCommand(command, client_socket_desc);

        // clean buffer
        memset(buffer, 0, strlen(buffer));
    }

    shutdown(client_socket_desc, SHUT_RDWR);
}