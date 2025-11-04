#include "processes.h"

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
    
    Process* process_ptr = getByProcessId(child_process_id);
    Process process = *process_ptr;
    resumeProcess(process.process_num, type);
}

void childProcess(char* command, pid_t process_id, ProcessType type)
{
    setpgid(0, 0);

    // initialize process behaviour on external signals
    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    
    signal(SIGCHLD, &onChildSignal);

    if (type == BACKGROUND)
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
        Process* process_ptr = getByProcessId(process_id);
        
        // skip processes not from application list
        if (process_ptr == NULL)
        {
            continue;
        }
        
        Process process = *process_ptr;

        // check if it's finished background process
        if (WIFEXITED(termination_status) && process.type == BACKGROUND)
        {
            printf("Background process (pid: %d) finished its job\n", process_id);
            removeProcessFromList(process.process_num);
            continue;
        }

        // check if it's externally terminated background job
        if (WIFSIGNALED(termination_status) && process.type == BACKGROUND)
        {
            printf("Background process (pid: %d) was terminated by external signal\n", process_id);
            removeProcessFromList(process.process_num);
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

void waitForProcess(pid_t process_id)
{
    Process* process_ptr = getByProcessId(process_id);
    
    if (process_ptr == NULL)
    {
        return;
    }

    Process process = *process_ptr;

    int termination_status;
    waitpid(process_id, &termination_status, WUNTRACED);

    // TODO:
    // resolve problem when program is stopped not because of a signall
    // is it possible with fg processes? 

    // check if process was stopped
    if (WIFSTOPPED(termination_status))
    {
        changeProcessState(process.process_num, STOPPED);
        return;
    }

    changeProcessState(process.process_num, DONE);
    removeProcessFromList(process.process_num);
}

void resumeProcess(int process_num, ProcessType type)
{
    if (process_num > process_count)
    {
        return;
    }

    Process* process_ptr = getByProcessNum(process_num);
    if (process_ptr == NULL)
    {
        return;
    }

    Process process = (*process_ptr);
    pid_t process_id = process.process_id;

    // resume process if previously it was stopped
    if (process.state == STOPPED && type != STOPPED)
    {
        int result = kill(process_id, SIGCONT);

        if (result < 0)
        {
            perror("Failed to move process back from suspension!");
        }
    }

    changeProcessState(process_num, RUNNING);
    changeProcessType(process_num, type);
    
    if (type == FOREGROUND)
    {
        // give console control to child process
        tcsetpgrp(STDIN_FILENO, process_id);

        waitForProcess(process_id);

        // getting console control back
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, global_group_id);
        signal(SIGTTOU, SIG_DFL);

        return;
    }
}

void changeProcessState(int process_num, ProcessState new_state)
{
    Process* process_ptr = getByProcessNum(process_num);
    if (process_ptr == NULL)
    {
        return;
    }

    (*process_ptr).state = new_state;
}

void changeProcessType(int process_num, ProcessType new_type)
{
    Process* process_ptr = getByProcessNum(process_num);
    if (process_ptr == NULL)
    {
        return;
    }

    (*process_ptr).type = new_type;
}

Process* getByProcessId(pid_t process_id)
{
    for (int i = 0; i < process_count; ++i)
    {
        if (process_list[i].process_id == process_id)
        {
            return &(process_list[i]);
        }
    }

    return NULL;
}

Process* getByProcessNum(int process_num)
{
    if (process_num > process_count)
    {
        return NULL;
    }

    return &(process_list[process_num - 1]);
}

void addProcessToList(pid_t process_id, char* command, ProcessType type)
{
    if (process_count == MAX_PROCESS_NUM - 1)
    {
        printf("Error: maximum number of processes has been reached");
    }
    
    // add process to list
    process_list[process_count].process_num = process_count + 1;
    process_list[process_count].process_id = process_id;
    strcpy(process_list[process_count].command, command);
    process_list[process_count].type = type;
    process_list[process_count].state = READY;

    process_count++;
}

void removeProcessFromList(int process_num)
{
    if (process_num > process_count)
    {
        return;
    }
    
    // remove process from processs list
    for (int i = process_num; i < process_count - 1; ++i)
    {
        process_list[i] = process_list[i + 1];
        process_list[i].process_num = i;
    }

    process_count--;
}