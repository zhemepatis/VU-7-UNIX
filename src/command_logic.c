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

    if (command == JOBS)
    {
        executeJobs();
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

    if (command == RESUME_AS_FG_PROCESS)
    {
        int process_num = parseResumeInFg(buffer);
        if (process_num != -1)
        {
            executeResumeFgProcess(process_num);
        }

        return;
    }
    
    if (command == RESUME_AS_BG_PROCESS)
    {
        int process_num = parseResumeInBg(buffer);
        if (process_num != -1)
        {
            executeResumeBgProcess(process_num);
        }

        return;
    }

    if (command == KILL_PROCESS)
    {
        int process_num = parseKill(buffer);
        if (process_num != -1)
        {
            executeKill(process_num);
        }

        return;
    }
}

void executeHelp()
{
    printf("SUPPORTED COMMANDS:\n");
    printf("& operator\t\t- command followed by this operator is executed in background\n");
    printf("jobs\t\t\t- lists jobs\n");
    printf("fg [process-number]\t- resumes job with specified number in foreground\n");
    printf("bg [process-number]\t- resumes job with specified number in background\n");
    printf("kill [process-number]\t- kills job with specified number\n");
    printf("help\t\t\t- prints help\n");
    printf("exit\t\t\t- exits shell\n");
}

void executeExit()
{
    printf("Thank you, come again!\n");
    exit(0);
}

void executeJobs()
{
    for (int i = 0; i < process_count; ++i)
    {
        char* status;
        Process curr_process = process_list[i];

        if (curr_process.state == READY)
        {
            printf("[%d] %d\tREADY\t\t%s\n", curr_process.process_num, curr_process.process_id, curr_process.command);
            continue;
        }

        if (curr_process.state == RUNNING)
        {
            printf("[%d] %d\tRUNNING\t\t%s\n", curr_process.process_num, curr_process.process_id, curr_process.command);
            continue;
        }

        if (curr_process.state == STOPPED)
        {
            printf("[%d] %d\tSTOPPED\t\t%s\n", curr_process.process_num, curr_process.process_id, curr_process.command);
            continue;
        }

        if (curr_process.state == DONE)
        {
            printf("[%d] %d\tDONE\t\t%s\n", curr_process.process_num, curr_process.process_id, curr_process.command);
            continue;
        }
    }
}

void executeCreateFgProcess(char* command)
{
    createProccess(command, FOREGROUND);
}

void executeCreateBgProcess(char* command)
{
    createProccess(command, BACKGROUND);
}

void executeResumeFgProcess(int process_num)
{
    resumeProcess(process_num, FOREGROUND);
}

void executeResumeBgProcess(int process_num)
{
    resumeProcess(process_num, BACKGROUND);
}

void executeKill(int process_num)
{
    Process* process_ptr = getByProcessNum(process_num);
    
    // check if such process exists
    if (process_ptr == NULL)
    {
        return;
    }

    // kill specified process
    Process process = *process_ptr;

    int result = kill(process.process_id, SIGKILL);
    if (result == -1)
    {
        printf("Error while trying to kill process: %d\n", process_num);
    }
}