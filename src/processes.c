#include "processes.h"

Process process_list[MAX_PROCESS_NUM];

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
    parentProcess(command, process_id, type);
}

void parentProcess(char* command, pid_t process_id, ProcessType type)
{
    addProcessToList(process_id, command, type);

    if (type == FOREGROUND)
    {
        waitForProcess(process_id);
        return;
    }

}

void childProcess(char* command, pid_t process_id, ProcessType type)
{
    // initialize behaviour on external signals
    //     signal(SIGINT,  SIG_DFL);
    //     signal(SIGQUIT, SIG_DFL);
    //     signal(SIGTSTP, SIG_DFL);
    //     signal(SIGTTIN, SIG_DFL);
    
    signal(SIGCHLD, &onChildSignal);

    if (type == FOREGROUND)
    {
        // TODO:
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

void onChildSignal(int signal)
{
    int termination_status;
    pid_t process_id;

    // check if process is valid
    if (process_id <= 0)
    {
        return;
    }

    // check if process is in process list
    Process* process = getByProcessId(process_id);
    if (process == NULL)
    {
        return;
    }
    
    // finished foreground processes are removed in wait loop 
    if (WIFEXITED(termination_status) && (*process).type == FOREGROUND)
    {
        return;
    }

    // remove finished background job
    if (WIFEXITED(termination_status) && (*process).type == BACKGROUND)
    {
        printf("Background process (pid: %d) finished its job\n", process_id);
        removeProcessFromList(process_id);
        return;
    }

    // check if process was terminated by external signal
    if (WIFSIGNALED(termination_status))
    {
        printf("Process (pid: %d) was killed by external signal\n", process_id);
        removeProcessFromList(process_id);
        return;
    }

    // check if process was stopped
    if (WIFSTOPPED(termination_status))
    {
        (*process).state = STOPPED;
        printf("Process (pid: %d) was stopped\n", process_id);
        return;
    }

    printf("undefined case\n");
    removeProcessFromList(process_id);
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

    while (waitpid(process_id, NULL, WNOHANG) == 0)
    {
        if ((*process).state == STOPPED)
        {
            return;
        }
    }

    removeProcessFromList(process_id);
}