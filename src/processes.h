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
    #include "structs/process.h"
    #include "enums/process_type.h"
    #include "enums/process_state.h"
    #include "string_operations.h"

    void addProcessToList(char* command, pid_t process_id);
    void removeProcessFromList(pid_t process_id);

    void createProccess(char* command, ProcessType type);
    void parentProcess(char* command, pid_t process_id, ProcessType type);
    void childProcess(char* command, pid_t process_id, ProcessType type);

    void onChildSignal(int signal);

#endif