#include "string_operations.h"

void appendChar(char* str, int* str_length_ptr, char character)
{
    int size = *str_length_ptr;
    str[size] = character;
    (*str_length_ptr)++;
}

void trim(char *str)
{
  int start = 0, end = strlen(str) - 1;

  // remove leading whitespace
  while (isspace(str[start]))
  {
    start++;
  }

  // remove trailing whitespace
  while (end > start && isspace(str[end]))
  {
    end--;
  }

  // adjust null terminator, if string was modified
  if (start > 0 || end < (strlen(str) - 1))
  {
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
  }
}

void split(char* command, char** token_array, int* token_num, int max_token_num)
{
  int idx = 0;
  char* token;

  while ((token = strtok(command, " ")) != NULL && idx < max_token_num)
  {
    token_array[idx] = token;
    idx++;
  }

  *token_num = idx;
}