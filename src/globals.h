#ifndef GLOBALS_H
    #define GLOBALS_H

    #include <sys/types.h>

    #define MAX_PROCESS_NUM 10
    
    #define MAX_INPUT_SIZE 256
    #define MAX_ARGS 64

    extern int process_count;
    extern pid_t global_group_id;

#endif