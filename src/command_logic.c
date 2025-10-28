#include "command_logic.h"

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
        // TODO:
        return;
    }

    if (command == MOVE_PROCESS_TO_FG)
    {
        // TODO:
        return;
    }

    if (command == CREATE_BG_PROCESS)
    {   
        // TODO:
        return;
    }

    if (command == RESUME_BG_PROCESS)
    {   
        // TODO:
        return;
    }

    if (command == KILL_PROCESS)
    {   
        // TODO:
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