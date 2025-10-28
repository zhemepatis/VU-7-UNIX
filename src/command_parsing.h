#ifndef COMMAND_PARSING_H
    #define COMMAND_PARSING_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "models/command.h"
    #include "string_operations.h"

    Command parseCommand(char* buffer);
    char* parseCreateNewFgProcesses(char* buffer);

#endif