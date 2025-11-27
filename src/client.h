#ifndef CLIENT_H
    #define CLIENT_H

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

    int main();
    void processConnection(int client_socket_desc);

#endif