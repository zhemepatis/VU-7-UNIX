#ifndef PROCESS_H
    #define PROCESS_H
    
    #include <sys/types.h>

    typedef struct
    {
        pid_t process_id;
        char* command;
    } Process;

#endif