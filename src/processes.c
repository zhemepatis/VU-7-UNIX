#include "processes.h"

Process process_list[MAX_PROCESS_NUM];

void addToProcessList(char* command, pid_t process_id)
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

void removeFromProcessList(int process_num)
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
        return;
    }

    if (process_id == ENOMEM)
    {
        return;
    }

    // execute command (child)
    if (process_id == 0)
    {
        // TODO:
        return;
    }

    // keep track of new process (parent)
    // TODO:
}