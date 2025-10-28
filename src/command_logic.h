#ifndef COMMAND_LOGIC_H
    #define COMMAND_LOGIC_H

    #include <stdio.h>
    #include <stdlib.h>

    #include "models/command.h"

    void executeCommand(Command command, char* buffer);
    void executeHelpCommand();
    void executeExitCommand();

#endif