#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operators.h"
#include "utils.h"

#define BUFFER_SIZE 50
#define MAX_TOKENS 3
#define TOKEN_DELIMS " \n\r\t"

static void ready_for_input() { printf(">  "); }

static char *read_line() {
  // put the input into a buffer
  char buffer[BUFFER_SIZE];
  int c;
  int len = 0;

  ready_for_input();

  while (true) {
    c = getchar();

    if (len >= BUFFER_SIZE) {
      // drop everything until EOF or newline
      while (c != EOF && c != '\n') c = getchar();
      printf("Calculations must be under 100 characters long.\n");
      return NULL;
    } else if (c == EOF || c == '\n') {
      return as_string(buffer, len);
    } else {
      buffer[len++] = c;
    }
  }
}

static char **split_args(char *line) {
  char **tokens = (char **)malloc(MAX_TOKENS * sizeof(char **));
  int position = 0;
  char *token;

  if (!tokens) {
    fprintf(stderr, "calculator: allocation error");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TOKEN_DELIMS);
  while (token != NULL) {
    if (position >= MAX_TOKENS) {
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

float calculate(char **tokens) {
  float result;
  float left, right;
  char *operation = tokens[1];

  left = strtod(tokens[0], NULL);
  right = strtod(tokens[2], NULL);

  if (*operation == get_operator(ADDITION).op_symbol) {
    result = left + right;
  } else if (*operation == get_operator(SUBTRACTION).op_symbol) {
    result = left - right;
  } else if (*operation == get_operator(MULTIPLICATION).op_symbol) {
    result = left * right;
  } else if (*operation == get_operator(DIVISION).op_symbol) {
    result = left / right;
  } else {
    return 0;
  }

  free(tokens);
  return result;
}

static void start_calculator() {
  char *line;
  char **tokens;
  float result;
  while (true) {
    line = read_line();
    if (!line) {
      continue;
    }

    tokens = split_args(line);
    if (!tokens) {
      continue;
    }

    result = calculate(tokens);
    printf("Result is: %g\n", result);
  }
}

int main() { start_calculator(); }
