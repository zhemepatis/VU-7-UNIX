#include "command_parsing.h"

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
        return MOVE_PROCESS_TO_FG;
    }

    if (strncmp(buffer, "bg", 2) == 0)
    {
        return RESUME_BG_PROCESS;
    }

    if (strcmp(buffer, "kill") == 0)
    {
        return KILL_PROCESS;
    }

    if (strstr(buffer, "&") != NULL && strlen(buffer) > 1)
    {
        return CREATE_BG_PROCESS;
    }

    return CREATE_FG_PROCESS;
}

char* parseCreateNewFgProcesses(char* buffer)
{   
    // TODO: implement
    trim(buffer);
}