#ifndef MAIN_H
    #define MAIN_H

    #include <stdio.h>
    #include <stdlib.h>

    #define MAX_INPUT_SIZE 256

    int main(int argc, char* args);
    
    void startShell();
    void appendChar(char* buffer, int* size_ptr, char character);
    void printPrompt(char* user_name, char* host_name, char* curr_dir);
    char* getCommand(char** command_buffer_ptr, int command_length);
    void appendChar(char* buffer, int* size_ptr, char character);
    
#endif