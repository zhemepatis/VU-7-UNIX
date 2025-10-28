#ifndef MAIN_H
    #define MAIN_H

    #include <stdio.h>
    #include <stdlib.h>

    #include "string_operations.h"
    #include "command_logic.h"
    #include "command_parsing.h"

    #define MAX_INPUT_SIZE 256

    int main(int argc, char* args);
    
    void startShell();
    void printPrompt(char* user_name, char* host_name, char* curr_dir);
    
#endif