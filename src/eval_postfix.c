#include "eval_postfix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "operators.h"
#include "utils.h"

#define BUFFER_SIZE 50

static float do_calculation(float left, float right, const char *operation) {
  float result;

  if (*operation == get_operator(ADDITION).op_symbol) {
    result = left + right;
  } else if (*operation == get_operator(SUBTRACTION).op_symbol) {
    result = left - right;
  } else if (*operation == get_operator(MULTIPLICATION).op_symbol) {
    result = left * right;
  } else if (*operation == get_operator(DIVISION).op_symbol) {
    result = left / right;
  } else if (*operation == get_operator(EXPONENTIATION).op_symbol) {
    result = pow(left, right);
  } else {
    return 0;
  }

  return result;
}

/*
General Plan:

3 3 +

iterate over each number in expression
if it is a number, add it to the stack
if it is an operator, do that operation on the top two values of the stack
  push the result of that operation back onto the stack

remember to free the input when you are finished

return whatever is on top of the stack when you have reached the final input
(should only be one thing there)
*/

float eval_postfix(const char **postfix_expression) {
  int i;
  int stack_position = 0;
  const char *current_token;
  float running_total = 0;
  float eval_stack[BUFFER_SIZE] = {
      0};  // TODO -- make this a dynamically resizing buffer

  for (i = 0; (current_token = postfix_expression[i]) != NULL; ++i) {
    if (is_num(current_token)) {
      eval_stack[stack_position++] = strtod(current_token, NULL);
    } else if (is_operator(current_token)) {
      // if stack_position is less than two, we just return 0

      // do operation
      running_total = do_calculation(
          (stack_position < 2 ? 0 : eval_stack[stack_position - 2]),
          eval_stack[stack_position - 1], current_token);

      if (stack_position >= 2) {
        eval_stack[stack_position - 2] = 0;
      }
      eval_stack[stack_position - 1] = 0;

      if (stack_position >= 2) {
        stack_position -= 2;
      } else {
        stack_position--;
      }

      eval_stack[stack_position++] = running_total;
    } else {
      // should not get here
      fprintf(stderr, "Unexpected value encountered at token %d", i);
      exit(EXIT_FAILURE);
    }
  }

  if (stack_position != 1) {
    fprintf(stderr, "Stack pointer became out of sync\n");
    exit(EXIT_FAILURE);
  }

  // free(postfix_expression);

  return eval_stack[stack_position - 1];
}