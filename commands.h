#ifndef COMMANDS_H
    #define COMMANDS_H

    #include <stdio.h>
    #include <string.h>

    typedef enum 
    {
        // general commands
        HELP,
        EXIT,

        // shell commands
        FOREGROUND,
        NEW_FOREGROUND_PROCESS,

        BACKGROUND,
        NEW_BACKGROUND_PROCESS,

        KILL
    } Command;

    Command parseCommand(char* buffer);

#endif