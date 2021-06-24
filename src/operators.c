#include "operators.h"

#include <stdio.h>
#include <stdlib.h>

#define NUM_OPERATIONS 5
#define OP_NOT_FOUND 6

static operator operator_data[] = {
    [EXPONENTIATION] = {RIGHT, HIGH, '^'},
    [MULTIPLICATION] = {LEFT, MIDDLE, '*'},
    [DIVISION] = {LEFT, MIDDLE, '/'},
    [ADDITION] = {LEFT, LOW, '+'},
    [SUBTRACTION] = {LEFT, LOW, '-'},
};

int operation_key(char token)
{
  int key;
  for (key = 0; key < NUM_OPERATIONS; ++key)
  {
    if (operator_data[key].op_symbol == token)
    {
      return key;
    }
  }

  return OP_NOT_FOUND;
}

operator get_operator(int key)
{
  return operator_data[key];
}
