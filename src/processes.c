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
        perror("System cannot create a new process");
        return;
    }
    
    if (process_id == ENOMEM)
    {
        perror("Not enough memory to create a new process");
        return;
    }
    
    // execute command (child)
    if (process_id == 0)
    {
        childProcess(command, process_id, type);
        
        // child shouldn't return here if command succeefully executed
        perror("Error executing command");
        exit(EXIT_FAILURE);
    }

    // keep track of new process (parent)
    // TODO:
    parentProcess(command, process_id, type);
}

void parentProcess(char* command, pid_t process_id, ProcessType type)
{
    if (type == BACKGROUND)
    {
        printf("Background process started with process id: %d\n", process_id);
    }

    if (type == FOREGROUND)
    {
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
}

void onChildSignal(int signal)
{
    // TODO: what to do, when child exits
}

