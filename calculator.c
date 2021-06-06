#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

static void ready_for_input()
{
  printf(">  ");
}

static char *as_string(char buffer[], int size)
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

static char *read_line()
{
  // put the input into a buffer
  char buffer[BUFFER_SIZE];
  int c;
  int len = 0;

  while (true)
  {
    c = getchar();

    if (len >= BUFFER_SIZE)
    {
      // drop everything until EOF or newline
      while (c != EOF && c != '\n')
        c = getchar();
      printf("Calculations must be under 100 characters long.\n");
      memset(buffer, 0, sizeof(buffer));
      len = 0;
      ready_for_input();
    }
    else if (c == EOF || c == '\n')
    {
      return as_string(buffer, len);
    }
    else
    {
      buffer[len++] = c;
    }
  }
}

static void start_calculator()
{
  ready_for_input();
  char *line = read_line();
  printf("input received : %s", line);
}

int main(int argc, char *argv[])
{
  start_calculator();
}