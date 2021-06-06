#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 50
#define MAX_TOKENS 3
#define TOKEN_DELIMS " \n\r\t"

static char *operations = "*/+-";

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

  ready_for_input();

  while (true)
  {
    c = getchar();

    if (len >= BUFFER_SIZE)
    {
      // drop everything until EOF or newline
      while (c != EOF && c != '\n')
        c = getchar();
      printf("Calculations must be under 100 characters long.\n");
      return NULL;
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

static char **parse_args(char *line)
{
  char **tokens = (char **)malloc(MAX_TOKENS * sizeof(char **));
  int position = 0;
  char *token;

  if (!tokens)
  {
    fprintf(stderr, "calculator: allocation error");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TOKEN_DELIMS);
  while (token != NULL)
  {
    if (position >= MAX_TOKENS)
    {
      printf("Only one operation allowed at a time. Please try again.\n");
      free(tokens);
      return NULL;
    }

    tokens[position++] = token;
    token = strtok(NULL, TOKEN_DELIMS);
  }

  // we do not need the line anymore, so we free it
  free(line);
  return tokens;
}

static void start_calculator()
{
  char *line;
  char **tokens;
  while (true)
  {
    line = read_line();
    if (!line)
    {
      continue;
    }

    tokens = parse_args(line);
    if (!tokens)
    {
      continue;
    }
  }
}

int main(int argc, char *argv[])
{
  start_calculator();
}