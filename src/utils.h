#ifndef UTILS_H

#define UTILS_H
#include <stdbool.h>


char *as_string(char buffer[], int size);

bool is_operator(const char *token);
bool is_num(const char *candidate);

bool is_l_parens(const char *token);
bool is_r_parens(const char *token);

#endif
