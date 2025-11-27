#ifndef SOCKETS_H
    #define SOCKETS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <poll.h>
    #include <stdbool.h>
    #include <time.h>

    #include "shared/constants.h"
    #include "logs.h"

    void readInfo(int client_socket_desc, char* buffer);
    void sendInfo(int client_socket_desc, char* buffer);

#endif