#ifndef COMMAND_PARSING_H
    #define COMMAND_PARSING_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "enums/parse_result.h"
    #include "enums/command.h"
    #include "string_operations.h"
    #include "constants.h"

    Command parseCommand(char* buffer);

    ParseResult parseCreateFgProcess(char* buffer);
    ParseResult parseCreateBgProcess(char* buffer);

    int parseResumeInFg(char* buffer);
    int parseResumeInBg(char* buffer);

    int parseKill(char* buff);

#endif