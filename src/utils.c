#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
