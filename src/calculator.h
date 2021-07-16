#ifndef CALCULATOR
#define CALCULATOR

#include <stdbool.h>

void start_calculator(void);
float calculate(const char **infix_expression, int expression_length);

#endif