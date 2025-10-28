#include "main.h"
#include "commands.h"

int main(int argc, char* args)
{
    startShell();
}

void startShell()
{
    // TODO: print greeting message (required)

    char temp_char = '*';
    while (temp_char != EOF)
    {
        // print shell prompt
        printPrompt("user_name", "host_name", "curr_dir");

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

        // TODO: parse command
        Command command = parseCommand(buffer);
        printf("Command: %d\n", command);


        // TODO: execute command
        // execute parsed command

        free(buffer);
    }
}

void printPrompt(char* user_name, char* host_name, char* curr_dir)
{
    printf("%s@%s:%s> ", user_name, host_name, curr_dir);
}

void appendChar(char* buffer, int* size_ptr, char character)
{
    int size = *size_ptr;
    buffer[size] = character;
    (*size_ptr)++;
}