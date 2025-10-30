#ifndef COMMAND_LOGIC_H
    #define COMMAND_LOGIC_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <signal.h>

    #include "enums/command.h"
    #include "command_parsing.h"
    #include "processes.h"

    void executeCommand(Command command, char* buffer);

    void executeHelp();
    void executeExit();
    
    void executeCreateFgProcess(char* command);
    void executeCreateBgProcess(char* command);

    void executeResumeFgProcess(int process_num);
    void executeResumeBgProcess(int process_num);

    void executeJobs();

    void executeKill(int process_num);

#endif