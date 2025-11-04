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

    if (strcmp(buffer, "jobs") == 0)
    {
        return JOBS;
    }

    if (strncmp(buffer, "fg", 2) == 0)
    {
        return RESUME_AS_FG_PROCESS;
    }

    if (strncmp(buffer, "bg", 2) == 0)
    {
        return RESUME_AS_BG_PROCESS;
    }

    if (strncmp(buffer, "kill", 4) == 0)
    {
        return KILL_PROCESS;
    }

    if (strstr(buffer, "&") != NULL && strlen(buffer) > 1)
    {
        return CREATE_BG_PROCESS;
    }

    return CREATE_FG_PROCESS;
}

ParseResult parseCreateFgProcess(char* buffer)
{   
    trim(buffer);
    return VALID_COMMAND;
}

ParseResult parseCreateBgProcess(char* buffer)
{
    trim(buffer);

    int buffer_length = strlen(buffer);
    char* ampersand_ptr = strstr(buffer, "&");

    if (ampersand_ptr == NULL)
    {
        printf("Error: not a backgroud process requested\n");
        return INVALID_COMMAND;
    }

    if (strstr(ampersand_ptr + 1 , "&") != NULL)
    {
        printf("Error: multiple background processes in one command are not supported\n");
        return INVALID_COMMAND;
    }

    if (ampersand_ptr != buffer + buffer_length - 1)
    {
        printf("Error: background commands with ampersand in the middle are not supported\n");
        return INVALID_COMMAND;
    }

    // remove ampersand character
    *ampersand_ptr = '\0';
    return VALID_COMMAND;
}

int parseResumeInFg(char* buffer)
{
    int argument_count;
    char* args[MAX_ARGS];

    split(buffer, args, &argument_count, MAX_ARGS);

    if (argument_count > 2)
    {
        printf("Error: too many arguments\n");
        return -1;
    }

    return atoi(args[1]);
}

int parseResumeInBg(char* buffer)
{
    int argument_count;
    char* args[MAX_ARGS];

    split(buffer, args, &argument_count, MAX_ARGS);

    if (argument_count > 2)
    {
        printf("Error: too many arguments\n");
        return -1;
    }

    return atoi(args[1]);
}

int parseKill(char* buffer)
{
    trim(buffer);

    int argument_count;
    char* args[MAX_ARGS];

    split(buffer, args, &argument_count, MAX_ARGS);

    if (argument_count > 2)
    {
        printf("Error: too many arguments\n");
        return -1;
    }

    return atoi(args[1]);
}