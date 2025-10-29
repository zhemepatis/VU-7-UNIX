#ifndef COMMAND_LOGIC_H
    #define COMMAND_LOGIC_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <signal.h>

    #include "models/command.h"
    #include "command_parsing.h"
    #include "processes.h"

    void executeCommand(Command command, char* buffer);

    void executeHelp();
    void executeExit();
    
    void executeCreateFgProcess(char* command);
    void executeCreateBgProcess(char* command);

    void executeKill(int process_num);

#endif