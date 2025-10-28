#ifndef STRING_OPERATIONS_H
    #define STRING_OPERATIONS_H

    #include <string.h>
    #include <ctype.h>

    void trim(char *str);
    void appendChar(char* buffer, int* size_ptr, char character);

#endif