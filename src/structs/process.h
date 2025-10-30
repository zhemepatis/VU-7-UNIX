#ifndef PROCESS_H
    #define PROCESS_H
    
    #include <sys/types.h>

    #include "../enums/process_type.h"
    #include "../enums/process_state.h"
    #include "../constants.h"

    typedef struct
    {
        pid_t process_id;
        char command[256];
        ProcessType type;
        ProcessState state;
    } Process;

#endif