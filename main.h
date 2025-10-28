#ifndef MAIN_H
    #define MAIN_H

    #include <stdio.h>
    #include <stdlib.h>

    #define MAX_INPUT_SIZE 256

    int main(int argc, char* args);
    
    void startShell();
    void appendChar(char* buffer, int* size_ptr, char character);
    
#endif