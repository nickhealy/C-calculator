#ifndef CALCULATOR
#define CALCULATOR

void start_calculator(void);
const char **split_args(char *line);
float calculate(const char **infix_expression, int expression_length);

#endif