#include "commands.h"

Command parseCommand(char* buffer)
{
    if (strcmp(buffer, "greet-me") == 0)
    {
        return GREET_ME;
    }

    if (strcmp(buffer, "exit") == 0)
    {
        return EXIT;
    }
}

void executeCommand(Command command, int client_socket_desc) 
{
    if (command == GREET_ME)
    {
        executeGreetMe(client_socket_desc);
        return;
    }
}

void executeGreetMe(int client_socket_desc)
{
    const char* buffer = "Hello, stranger!";
    int buffer_length = strlen(buffer);

    sendInfo(client_socket_desc, buffer);
}

void executeExit(int client_socket_desc)
{
    shutdown(client_socket_desc, SHUT_RDWR);
}