#ifndef MAIN_H
    #define MAIN_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <signal.h>

    #include "string_operations.h"
    #include "processes.h"
    #include "command_logic.h"
    #include "command_parsing.h"
    #include "globals.h"

    int main(int argc, char* args);
    
    void initShell();
    void startShell();
    
    void printPrompt(char* user_name, char* host_name, char* curr_dir);
    
#endif