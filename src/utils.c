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

bool is_minus(const char candidate) { return candidate == '-'; }
bool is_decimal(const char candidate) { return candidate == '.'; }

bool is_num(const char *candidate) {
  char curr_char;
  int i = 0;
  bool num_incomplete = false;

  while ((curr_char = candidate[i++]) != '\0') {
    if ((curr_char < '0' || curr_char > '9') && !is_minus(curr_char) &&
        !is_decimal(curr_char)) {
      return false;
    }

    if (is_minus(curr_char) || is_decimal(curr_char)) {
      num_incomplete = true;
    } else {
      num_incomplete = false;
    }
  }

  return num_incomplete ? false : true;
}

bool is_l_parens(const char *token) { return *token == '('; }

bool is_r_parens(const char *token) { return *token == ')'; }