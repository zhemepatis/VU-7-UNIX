#ifndef COMMAND_H
    #define COMMAND_H

    typedef enum 
    {
        // general commands
        HELP,
        EXIT,
        // shell commands
        CREATE_FG_PROCESS,
        MOVE_PROCESS_TO_FG,
        CREATE_BG_PROCESS,
        RESUME_BG_PROCESS,
        KILL_PROCESS
    } Command;

#endif