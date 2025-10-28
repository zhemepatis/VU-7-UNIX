#ifndef COMMANDS_H
    #define COMMANDS_H

    typedef enum 
    {
        // general commands
        HELP,
        EXIT,
        // shell commands
        FOREGROUND,
        BACKGROUND,
        KILL
    } Command;

#endif