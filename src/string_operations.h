#ifndef STRING_OPERATIONS_H
    #define STRING_OPERATIONS_H

    #include <string.h>
    #include <ctype.h>

    void appendChar(char* buffer, int* size_ptr, char character);
    void trim(char *str);
    void split(char* command, char** token_array, int* token_num, int max_token_num);

#endif