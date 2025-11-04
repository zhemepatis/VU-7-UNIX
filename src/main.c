#include "main.h"

int main(int argc, char* args)
{
    initShell();
    startShell();
}

void initShell()
{
    global_group_id = getpgrp();

    // initialize behaviour on external signals
    signal(SIGINT,  SIG_IGN); // ^C signal
    signal(SIGTSTP, SIG_IGN); // ^Z signal
    signal(SIGTTIN, SIG_IGN); // terminal input signal
    signal(SIGTTOU, SIG_IGN); // terminal output signal

    signal(SIGCHLD, &onChildSignal);
}

void startShell()
{
    printf("Shell program has been started\n");

    char temp_char = '*';
    while (temp_char != EOF)
    {
        // print shell prompt
        printf("shell> ");

        // process user input
        temp_char = getchar();

        // check if user entered a newline on empty prompt
        if (temp_char == '\n')
        {
            continue;
        }

        // check if it isn't EOF character
        if (temp_char == EOF)
        {
            continue;
        }
        
        // consider input as a command
        char* buffer = malloc(sizeof(char) * MAX_INPUT_SIZE);
        int buffer_length = 0;

        // append previous character to buffer
        appendChar(buffer, &buffer_length, temp_char);

        // get the rest of the buffer
        while ((temp_char = getchar()) != '\n' && buffer_length < MAX_INPUT_SIZE - 1)
        {
            appendChar(buffer, &buffer_length, temp_char);
        }

        // append string termination character
        buffer[buffer_length] = '\0';

        // parse & execute command
        Command command = parseCommand(buffer);
        executeCommand(command, buffer);

        free(buffer);
    }
}