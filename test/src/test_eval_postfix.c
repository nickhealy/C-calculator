#include <stdio.h>
#include <stdlib.h>

#include "eval_postfix.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(EvalPostfix);

TEST_SETUP(EvalPostfix) {
  // set stuff up here
}

TEST_TEAR_DOWN(EvalPostfix) {
  // tear stuff down here
}

TEST(EvalPostfix, evals_simple_expressions) {
  const char *expression1[] = {"3", "3", "+", NULL};
  const char *expression2[] = {"3", "3", "*", NULL};
  const char *expression3[] = {"9", "3", "/", NULL};
  const char *expression4[] = {"5", "2", "-", NULL};
  const char *expression5[] = {"2", "3", "^", NULL};
  const char *expression6[] = {"2", "2", "-", NULL};
  const char *expression7[] = {"2", "5", "-", NULL};
  TEST_ASSERT_EQUAL_FLOAT(6.00, eval_postfix(expression1));
  TEST_ASSERT_EQUAL_FLOAT(9.00, eval_postfix(expression2));
  TEST_ASSERT_EQUAL_FLOAT(3.00, eval_postfix(expression3));
  TEST_ASSERT_EQUAL_FLOAT(9.00, eval_postfix(expression2));
  TEST_ASSERT_EQUAL_FLOAT(3.00, eval_postfix(expression4));
  TEST_ASSERT_EQUAL_FLOAT(8.00, eval_postfix(expression5));
  TEST_ASSERT_EQUAL_FLOAT(0.00, eval_postfix(expression6));
  TEST_ASSERT_EQUAL_FLOAT(-3.00, eval_postfix(expression7));
}

TEST(EvalPostfix, evals_complex_expressions) {
  const char *expression1[] = {"3", "7", "+", "2", "*", "8", "-", NULL};
  TEST_ASSERT_EQUAL_FLOAT(12.000, eval_postfix(expression1));
}
