#include "processes.h"

Process process_list[MAX_PROCESS_NUM];

void createProccess(char* command, ProcessType type)
{
    int fork_result = fork();
    
    // check for errors
    if (fork_result == -1)
    {
        perror("Error while creating a fork");
        return;
    }

    // execute command (child)
    if (fork_result == 0)
    {
        pid_t process_id = getpid();
        childProcess(command, process_id, type);
        
        // child shouldn't return here if command succeefully executed
        perror("Error executing command");
        exit(EXIT_FAILURE);
    }

    // keep track of new process (parent)
    parentProcess(command, fork_result, type);
}

void parentProcess(char* command, pid_t child_process_id, ProcessType type)
{
    addProcessToList(child_process_id, command, type);

    if (type == FOREGROUND)
    {
        waitForProcess(child_process_id);

        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, global_group_id);
        signal(SIGTTOU, SIG_DFL);

        return;
    }

    if (type == BACKGROUND)
    {
        // TODO: what parent does for bg processes?
    }
}

void childProcess(char* command, pid_t process_id, ProcessType type)
{
    // initialize behaviour on external signals
    signal(SIGINT,  SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    
    signal(SIGCHLD, &onChildSignal);

    if (type == FOREGROUND)
    {
        tcsetpgrp(STDIN_FILENO, process_id);
    }
    else if (type == BACKGROUND)
    {
        printf("Background process (pid: %d) has been started\n", process_id);
    }

    // get args
    int argument_count;
    char* args[MAX_ARGS];
    
    split(command, args, &argument_count, MAX_ARGS - 1);
    args[argument_count] = NULL;
    
    // run the command
    execvp(args[0], args);
}

void onChildSignal(int signal) {
    pid_t process_id;
    int termination_status;

    while ((process_id = waitpid(-1, &termination_status, WNOHANG | WUNTRACED)) > 0) {
        Process* process = getByProcessId(process_id);
        
        // skip processes not from application list
        if (process == NULL)
        {
            continue;
        }

        // check if it's finished background process
        if (WIFEXITED(termination_status) && (*process).type == BACKGROUND)
        {
            printf("Background process (pid: %d) finished its job\n", process_id);
            removeProcessFromList(process_id);
            continue;
        }

        // check if it's externally terminated background job
        if (WIFSIGNALED(termination_status) && (*process).type == BACKGROUND)
        {
            printf("Background process (pid: %d) was terminated by external signal\n", process_id);
            removeProcessFromList(process_id);
            continue;
        }

        // check if process was stopped
        if (WIFSTOPPED(termination_status))
        {
            changeProcessState(process_id, STOPPED);
            printf("Process (pid: %d) was stopped\n", process_id);
            continue;
        }
    }
}

Process* getByProcessId(pid_t process_id)
{
    for (int idx = 0; idx < process_count; ++idx)
    {
        if (process_list[idx].process_id == process_id)
        {
            return &(process_list[idx]);
        }
    }

    return NULL;
}

void addProcessToList(pid_t process_id, char* command, ProcessType type)
{
    if (process_count == MAX_PROCESS_NUM - 1)
    {
        printf("Error: maximum number of processes has been reached");
    }
    
    // add process to list
    process_list[process_count].process_id = process_id;
    strcpy(process_list[process_count].command, command);
    process_list[process_count].state = TO_BE_STARTED;
    process_list[process_count].type = type;

    process_count++;
}

void removeProcessFromList(pid_t process_id)
{
    int removal_needed = false;
    int idx;

    for (int i = 0; i < process_count; ++i)
    {
        if (process_list[i].process_id == process_id)
        {
            idx = i;
            removal_needed = true;
            break;
        }
    }

    if (!removal_needed)
    {
        return;
    }

    // remove process from processs list
    for (int i = idx; i < process_count - 1; ++i)
    {
        process_list[i] = process_list[i + 1];
    }

    process_count--;
}

void waitForProcess(pid_t process_id)
{
    Process* process = getByProcessId(process_id);
    
    if (process == NULL)
    {
        return;
    }

    int termination_status;
    waitpid(process_id, &termination_status, WUNTRACED);

    // TODO:
    // resolve problem when program is stopped not because of a signall
    // is it possible with fg processes? 

    // check if process was stopped
    if (WIFSTOPPED(termination_status))
    {
        changeProcessState(process_id, STOPPED);
        return;
    }

    removeProcessFromList(process_id);
}

void changeProcessState(pid_t process_id, ProcessState new_state)
{
    Process* process = getByProcessId(process_id);
    if (process == NULL)
    {
        return;
    }

    (*process).state = new_state;
}