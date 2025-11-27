#ifndef COMMANDS_H
    #define COMMANDS_H

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

    #include "enums/command.h"
    #include "sockets.h"

    Command parseCommand(char* buffer);

    void executeCommand(Command command, int client_socket_desc);
    void executeGreetMe(int client_socket_desc);
    void executeExit(int client_socket_desc);

#endif