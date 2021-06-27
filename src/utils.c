#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *as_string(char buffer[], int size) {
  char *result = (char *)malloc((size + 1) * sizeof(char));
  if (!result) {
    fprintf(stderr, "calculator: allocation error");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    result[i] = buffer[i];
  }
  result[size] = '\0';
  return result;
}

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

bool is_operator(const char *token) { return is_in_group(*token, operators); }

bool is_num(const char *candidate) {
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

bool is_l_parens(const char *token) { return *token == '('; }

bool is_r_parens(const char *token) { return *token == ')'; }