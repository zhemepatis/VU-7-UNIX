#ifndef COMMAND_H
    #define COMMAND_H

    typedef enum 
    {
        // general commands
        HELP,
        EXIT,
        // shell commands
        JOBS,
        CREATE_FG_PROCESS,
        CREATE_BG_PROCESS,
        RESUME_AS_FG_PROCESS,
        RESUME_AS_BG_PROCESS,
        KILL_PROCESS
    } Command;

#endif