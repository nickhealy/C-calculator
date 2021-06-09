#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

char *as_string(char buffer[], int size)
{
  char *result = (char *)malloc((size + 1) * sizeof(char));
  if (!result)
  {
    fprintf(stderr, "calculator: allocation error");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++)
  {
    result[i] = buffer[i];
  }
  result[size] = '\0';
  return result;
}

int to_int(char *character)
{
  // '1' -> 1
  // '564' -> 564
  int i;
  int converted = 0;

  for (i = 0; character[i] != '\0'; ++i)
  {
    converted = converted * 10 + character[i] - '0';
  }

  return converted;
}