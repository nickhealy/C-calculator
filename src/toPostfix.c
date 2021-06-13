#include "toPostfix.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <stdbool.h>

static const char *operators = "+-*/";
static const char *valid_nums = "1234567890.";

static bool is_in_group(char candidate, const char *group)
{
  int i;
  for (i = 0; group[i] != '\0'; ++i)
  {
    if (group[i] == candidate)
    {
      return true;
    }
  }
  return false;
}

static bool is_operator(char *token)
{
  return is_in_group(*token, operators);
}

static bool is_l_parens(char *token)
{
  return *token == '(';
}

static bool is_r_parens(char *token)
{
  return *token == ')';
}

static bool is_num(char *candidate)
{
  // for now this will work -- in the future we will want better error handling with validation, etc.
  int i;
  for (i = 0; candidate[i] != '\0'; ++i)
  {
    if (is_in_group(candidate[i], valid_nums))
    {
      continue;
    }
    return false;
  }

  return true;
}

// this is an implementation of Djikstra's Shunting Yard Algorithm

char **to_postfix(char **infix, int length)
{
  int read_count = 0;
  int output_position = 0;
  int operator_position = 0;

  char **output = malloc(length * sizeof(char *));
  char *operator_stack[length];
  char *current_token;

  while (read_count < length)
  {
    current_token = infix[read_count++];
    if (is_num(current_token))
    {
      output[output_position++] = current_token;
    }
    else if (is_operator(current_token))
    {
      operator_stack[operator_position++] = current_token;
    }
    else if (is_l_parens(current_token))
    {
      operator_stack[operator_position++] = current_token;
    }
    else if (is_r_parens(current_token))
    {
    }
  }

  while (operator_position > 0)
  {
    output[output_position++] = operator_stack[--operator_position];
  }

  return output;
}
