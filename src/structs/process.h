#ifndef PROCESS_H
    #define PROCESS_H
    
    #include <sys/types.h>

    #include "../enums/process_state.h"

    typedef struct
    {
        pid_t process_id;
        char* command;
        ProcessState state;
    } Process;

#endif