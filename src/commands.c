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

char* parseNewForegroundProcessesCommand(char* buffer)
{
    return trim(buffer);
}

void executeCommand(Command command, char* buffer)
{
    if (command == HELP) 
    {
        executeHelpCommand();
        return;
    }

    if (command == EXIT)
    {
        executeExitCommand();
        return;
    }

    if (command == CREATE_FG_PROCESS)
    {
        executeNewForegroundProcessesCommand(buffer);
    }
}

void executeHelpCommand()
{
    // TODO: add full implementation
    printf("Printing help\n");
}

void executeExitCommand()
{
    printf("Thank you, come again!\n");
    exit(0);
}

char* executeNewForegroundProcessesCommand(char* buffer)
{
    
}