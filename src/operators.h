#ifndef OPERATORS_H
#define OPERATORS_H

typedef enum
{
  ADDITION = 0,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION,
  EXPONENTIATION
} op_symbol_keys;

typedef enum
{
  LEFT,
  RIGHT
} associativity_type;

typedef enum
{
  LOW,
  MIDDLE,
  HIGH
} precedence_type;

typedef struct t_operator
{
  associativity_type associativity;
  precedence_type precedence;
  char op_symbol;
}
operator;

int operation_key(char token);

operator get_operator(int key);

char op_symbol(op_symbol_keys key);

#endif
