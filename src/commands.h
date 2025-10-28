#ifndef COMMANDS_H
    #define COMMANDS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    

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

    Command parseCommand(char* buffer);

    void executeCommand(Command command, char* buffer);
    void executeHelpCommand();
    void executeExitCommand();

#endif