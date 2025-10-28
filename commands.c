#include "commands.h"

Command parseCommand(char* buffer)
{
    if (strcmp(buffer, "help") == 0) 
    {
        return HELP;
    }

    if (strcmp(buffer, "exit") == 0)
    {
        return EXIT;
    }

    if (strncmp(buffer, "fg", 2) == 0)
    {
        return FOREGROUND;
    }

    if (strncmp(buffer, "bg", 2) == 0)
    {
        return BACKGROUND;
    }

    if (strcmp(buffer, "kill") == 0)
    {
        return KILL;
    }

    if (strstr(buffer, "&") != NULL && strlen(buffer) > 1)
    {
        return NEW_BACKGROUND_PROCESS;
    }

    return NEW_FOREGROUND_PROCESS;
}