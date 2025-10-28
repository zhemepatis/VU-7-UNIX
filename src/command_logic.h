#ifndef COMMAND_LOGIC_H
    #define COMMAND_LOGIC_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <signal.h>

    #include "models/command.h"
    #include "command_parsing.h"

    void executeCommand(Command command, char* buffer);
    void executeHelp();
    void executeExit();
    void executeKill(int process_num);

#endif