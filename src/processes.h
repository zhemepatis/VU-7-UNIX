#ifndef PROCESSES_H
    #define PROCESSES_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <errno.h>
    #include <signal.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/wait.h>

    #include "globals.h"
    #include "models/process.h"
    #include "models/process_type.h"
    #include "string_operations.h"

    void addProcessToList(char* command, pid_t process_id);
    void removeProcessFromList(int process_num);

    void createProccess(char* command, ProcessType type);
    void parentProcess(char* command, pid_t process_id, ProcessType type);
    void childProcess(char* command, pid_t process_id, ProcessType type);

    void onChildSignal(int signal);

#endif