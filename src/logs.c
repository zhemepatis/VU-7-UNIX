#include "logs.h"

void logMessage(char* author, char* buffer) 
{
    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);
    
    char* ts = asctime(local_time);
    ts[strcspn(ts, "\n")] = '\0';
    
    printf("[%s] %s: %s\n", ts, author, buffer);
}