#ifndef SPLIT_ARGS
#define SPLIT_ARGS

#include <stdbool.h>

bool is_valid_token(const char *curr_token, char to_add, bool neg_possible);
const char **split_args(char *line, int *num_tokens); 
#endif
