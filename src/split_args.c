#include "split_args.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_TOKENS 50

#define is_decimal(character) (character == '.')
#define is_num(character) (character >= '0' && character <= '9')
#define is_operator(character)                                 \
  (character == '-' || character == '+' || character == '/' || \
   character == '*' || character == '^')
#define is_l_parens(character) (character == '(')

bool is_parens(char test);

bool is_parens(char test) { return (test == '(' || test == ')'); }

bool is_valid_token(const char *curr_token, char to_add, bool neg_possible) {
  char last_char;
  int i = 0;
  int token_length = strlen(curr_token);
  bool decimal_possible = true;

  while (i < token_length) {
    last_char = curr_token[i++];

    if (is_decimal(last_char)) {
      decimal_possible = false;
    }
  }

  // will definitely return false when adding -, +, /, *, ^, (, ,)
  if (is_operator(to_add) || is_parens(to_add)) {
    return false;
  }

  // adding a number will always be valid if the last char is another number, or
  // a .
  if (is_num(to_add) && (is_num(last_char) || is_decimal(last_char))) {
    return true;
  }

  // can add a decimal to a number, and only if we haven't yet seen a decimal
  if (is_decimal(to_add) && is_num(last_char) && decimal_possible) {
    return true;
  }

  // if we are buildling a negative
  if (((is_decimal(to_add) && decimal_possible) || is_num(to_add)) &&
      is_minus(last_char) && neg_possible) {
    return true;
  }

  return false;
}

// go through everline of string, adding it to the current token as long as it
// would be valid to do so

static char *resize_buffer(char *curr_buffer, int length) {
  char *new_buffer = realloc(curr_buffer, length * sizeof(char *));
  if (!new_buffer) {
    fprintf(stderr, "resize_buffer: allocation error");
    exit(EXIT_FAILURE);
  }
  return new_buffer;
}

const char **split_args(char *line, int *num_tokens) {
  const char **tokens =
      (const char **)malloc(MAX_TOKENS * sizeof(const char **));
  int token_count = 0;
  int token_length = 0;
  int i = 0;
  char *token_buffer = (char *)malloc(token_length * sizeof(char *));
  bool neg_possible = true;
  char curr_char;  // holds current token we are building

  while ((curr_char = line[i++]) != '\0') {
    if (curr_char == ' ' || curr_char == '\t' || curr_char == '\r') {
      continue;
    }

    if (token_length == 0) {
      token_buffer[token_length++] = curr_char;
      continue;
    }

    // if it would be ok to add next char, add it
    if (is_valid_token(token_buffer, curr_char, neg_possible)) {
      token_buffer = resize_buffer(token_buffer, token_length);
      token_buffer[token_length++] = curr_char;

      if (is_minus(curr_char)) {
        neg_possible = true;
      }

    } else {
      // otherwise, add the current token to the output
      tokens[token_count++] = as_string(token_buffer, token_length);
      // we need to zero out the buffer, or else it will confuse is_valid_token
      memset(token_buffer, 0, token_length);
      token_length = 0;
      neg_possible = false;
      i--;
    }
  }

  // load any tokens-in-progress into the output
  tokens[token_count++] = as_string(token_buffer, token_length);
  free(token_buffer);

  *num_tokens = token_count;
  return tokens;
}