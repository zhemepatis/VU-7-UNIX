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

void parseForegroundCommand(char* buffer)
{
    // TODO:
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