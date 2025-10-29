#include "processes.h"

Process process_list[MAX_PROCESS_NUM];

void addProcessToList(char* command, pid_t process_id)
{
    if (process_count == MAX_PROCESS_NUM)
    {
        printf("Error: maximum number of processes has been reached");
    }

    // add process to list
    process_list[process_count].process_id = process_id;
    strcpy(process_list[process_count].command, command);
    process_count++;
}

void removeProcessFromList(int process_num)
{
    int processRemoved = true;

    // TODO: finish   
}

void createProccess(char* command, ProcessType type)
{
    pid_t process_id = fork();

    // check for errors
    if (process_id == EAGAIN)
    {
        printf("Error: system cannot create a new porcess\n");
        return;
    }

    if (process_id == ENOMEM)
    {
        printf("Error: not enough memory to create a new process\n");
        return;
    }

    // execute command (child)
    if (process_id == 0)
    {
        childProcess(command, process_id, type);
    }

    // keep track of new process (parent)
    // TODO:
    parentProcess(command, process_id, type);
}

void parentProcess(char* command, pid_t process_id, ProcessType type)
{
    if (type == BACKGROUND)
    {
        // TODO:
    }

    if (type == FOREGROUND)
    {
        // TODO:
        waitpid(process_id, NULL, 0);
    }
}

void childProcess(char* command, pid_t process_id, ProcessType type)
{
    // initialize behaviour on external signals
//     signal(SIGINT,  SIG_DFL);
//     signal(SIGQUIT, SIG_DFL);
//     signal(SIGTSTP, SIG_DFL);
//     signal(SIGTTIN, SIG_DFL);

//     signal(SIGCHLD, &onChildSignal);

    // get args
    int argument_count;
    char* args[MAX_ARGS];

    split(command, args, &argument_count, MAX_ARGS - 1);
    args[argument_count] = NULL;

    // run the command
    execvp(args[0], args);

    printf("Error: something went wrong executing command '%s'\n", command);
}

void onChildSignal(int signal)
{
    // TODO: what to do, when child exits
}

