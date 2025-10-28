#include "main.h"

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

        // process user input as command input
        char* command_buffer = malloc(sizeof(char) * MAX_INPUT_SIZE);
        int command_length = 0;

        // append first character to command
        appendChar(command_buffer, &command_length, temp_char);

        while (command_length < MAX_INPUT_SIZE)
        {
            printf("loop iteration.\n");
            temp_char = getchar();

            // check if it is end of user input
            if (temp_char == '\n')
            {
                command_buffer[command_length] = '\0';

                // TODO: parse command
                // TODO: execute command

                break;
            }
            
            appendChar(command_buffer, &command_length, temp_char);
        }
    }
}

void appendChar(char* buffer, int* size_ptr, char character)
{
    int size = *size_ptr;
    buffer[size] = character;
    (*size_ptr)++; 
}