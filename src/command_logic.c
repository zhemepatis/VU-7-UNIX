#include "command_logic.h"

void executeCommand(Command command, char* buffer)
{
    if (command == HELP) 
    {
        executeHelp();
        return;
    }

    if (command == EXIT)
    {
        executeExit();
        return;
    }

    if (command == CREATE_FG_PROCESS)
    {
        ParseResult parseResult = parseCreateFgProcess(buffer);
        if (parseResult != INVALID_COMMAND)
        {
            executeCreateFgProcess(buffer);
        }

        return;
    }

    if (command == CREATE_BG_PROCESS)
    {
        ParseResult parseResult = parseCreateBgProcess(buffer);
        if (parseResult != INVALID_COMMAND)
        {
            executeCreateBgProcess(buffer);
        }

        return;
    }

    if (command == MOVE_PROCESS_TO_FG)
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
        int arg = parseKill(buffer);
        executeKill(arg);
        return;
    }
}

void executeHelp()
{
    // TODO: add full implementation
    printf("Printing help\n");
}

void executeExit()
{
    printf("Thank you, come again!\n");
    exit(0);
}

void executeCreateFgProcess(char* command)
{
    createProccess(command, FOREGROUND);
}

void executeCreateBgProcess(char* command)
{
    createProccess(command, BACKGROUND);
}

void executeKill(int process_num) 
{
    int result = kill(process_num, SIGKILL);

    if (result == -1)
    {
        printf("Error while trying to kill process: %d\n", process_num);
    }
}