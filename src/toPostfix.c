#include "toPostfix.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operators.h"

static bool should_pop_operator(const char *stack_operator,
                                const char *curr_operator);
static bool is_in_group(const char candidate, const char *group);
static bool is_operator(const char *token);
static bool is_l_parens(const char *token);
static bool is_r_parens(const char *token);
static bool is_num(const char *candidate);

static const char *operators = "^*/+-";
static const char *valid_nums = "1234567890.";

static bool is_in_group(const char candidate, const char *group) {
  int i;
  for (i = 0; group[i] != '\0'; ++i) {
    if (group[i] == candidate) {
      return true;
    }
  }
  return false;
}

static bool is_operator(const char *token) {
  return is_in_group(*token, operators);
}

static bool is_l_parens(const char *token) { return *token == '('; }

static bool is_r_parens(const char *token) { return *token == ')'; }

static bool is_num(const char *candidate) {
  // for now this will work -- in the future we will want better error handling
  // with validation, etc.
  int i;
  for (i = 0; candidate[i] != '\0'; ++i) {
    if (is_in_group(candidate[i], valid_nums)) {
      continue;
    }
    return false;
  }

  return true;
}

static bool should_pop_operator(const char *stack_operator,
                                const char *curr_operator) {
  operator curr_op_data = get_operator(operation_key(*curr_operator));
  operator stack_op_data = get_operator(operation_key(*stack_operator));

  return is_operator(curr_operator) && !is_l_parens(stack_operator) &&
         ((curr_op_data.precedence <= stack_op_data.precedence &&
           curr_op_data.associativity == LEFT) ||
          (curr_op_data.precedence < stack_op_data.precedence &&
           curr_op_data.associativity == RIGHT));
}

// this is an implementation of Djikstra's Shunting Yard Algorithm

const char **to_postfix(const char **infix, int length) {
  int read_count = 0;
  int output_position = 0;
  int operator_position = 0;

  // we add one to account for NULL pointer at end, in case there are no
  // parenthesis in the array that get eliminated
  const char **output = malloc((length + 1) * sizeof(char *));
  const char *operator_stack[length];
  const char *current_token;

  while (read_count < length) {
    current_token = infix[read_count++];
    if (is_num(current_token)) {
      output[output_position++] = current_token;
    } else if (is_operator(current_token)) {
      while (operator_position > 0 &&
             should_pop_operator(operator_stack[operator_position - 1],
                                 current_token)) {
        output[output_position++] = operator_stack[--operator_position];
      }
      operator_stack[operator_position++] = current_token;
    } else if (is_l_parens(current_token)) {
      operator_stack[operator_position++] = current_token;
    } else if (is_r_parens(current_token)) {
      while (operator_position > 0 &&
             !is_l_parens(operator_stack[operator_position - 1])) {
        output[output_position++] = operator_stack[--operator_position];
      }
      // if we have not found a left parens by now, then we had mismatched
      // parens
      if (operator_position == 0) {
        fprintf(stderr,
                "Mismatched parenthesis detected. Found \")\" without matching "
                "\")\".\n");
        return NULL;
      }

      // discard
      operator_position--;
    }
  }

  while (operator_position > 0) {
    current_token = operator_stack[--operator_position];
    if (is_l_parens(current_token)) {
      fprintf(stderr,
              "Mismatched parenthesis detected. Found \"(\" without matching "
              "\")\".\n");
      return NULL;
    }
    output[output_position++] = current_token;
  }

  // add null pointer so we know where array ends
  output[output_position] = (char *)NULL;

  return output;
}
