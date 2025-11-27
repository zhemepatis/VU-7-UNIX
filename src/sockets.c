#include "sockets.h"

void readInfo(int client_socket_desc, char* buffer) 
{
    ssize_t recv_result = -1;
    
    while (true)
    {
        recv_result = recv(client_socket_desc, buffer, BUFFER_SIZE, 0);

        if (recv_result < 0)
        {
           // wait for input
            if (errno == EAGAIN)
            {
                struct pollfd polled_desc;
                polled_desc.fd = client_socket_desc;
                polled_desc.events = POLLIN;

                int poll_result = poll(&polled_desc, 1, -1);
                continue;
            }

            perror("recv");
            break;
        }

        logMessage("CLIENT", buffer);

        break;
    }
}

void sendInfo(int client_socket_desc, char* buffer) 
{
    ssize_t send_result = -1;
    
    while (true)
    {
        send_result = send(client_socket_desc, buffer, strlen(buffer), 0);

        if (send_result < 0)
        {
           // wait for output
            if (errno == EAGAIN)
            {
                struct pollfd polled_desc;
                polled_desc.fd = client_socket_desc;
                polled_desc.events = POLLOUT;

                int poll_result = poll(&polled_desc, 1, -1);
                continue;
            }

            perror("send");
            break;
        }

        logMessage("SERVER", buffer);

        break;
    }
}