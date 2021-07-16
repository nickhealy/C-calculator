#include "calculator.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval_postfix.h"
#include "operators.h"
#include "split_args.h"
#include "toPostfix.h"
#include "utils.h"

#define BUFFER_SIZE 50
#define MAX_TOKENS 30
#define TOKEN_DELIMS " \n\r\t"
#define last_index(current_index) (current_index > 0 ? current_index - 1 : 0)

static char *read_line(void);
static void ready_for_input(void);

static void ready_for_input() { printf(">  "); }

// for keeping track of how many tokens we are evaluating
static int num_tokens = 0;

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

float calculate(const char **infix_expression, int expression_length) {
  const char **postfix_expression =
      to_postfix(infix_expression, expression_length);
  float result;
  if (!postfix_expression) {
    fprintf(stderr, "Could not convert to postfix\n");
    exit(EXIT_FAILURE);
  }

  result = eval_postfix(postfix_expression);

  return result;
}

void start_calculator() {
  char *line;
  const char **tokens;
  float result;
  while (true) {
    line = read_line();
    if (!line) {
      continue;
    }

    tokens = split_args(line, &num_tokens);
    if (!tokens) {
      continue;
    }

    result = calculate(tokens, num_tokens);
    printf("Result is: %g\n", result);
  }
}
