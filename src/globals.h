#ifndef GLOBALS_H
    #define GLOBALS_H

    #include <sys/types.h>

    #include "structs/process.h"
    #include "constants.h"

    extern int process_count;
    extern pid_t global_group_id;
    extern Process process_list[MAX_PROCESS_NUM];

#endif