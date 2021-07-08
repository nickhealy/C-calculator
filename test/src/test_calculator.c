#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Calculator);

static int test_num_tokens = 0;

void reset(const char **result);

TEST_SETUP(Calculator) {
  // set stuff up here
}

TEST_TEAR_DOWN(Calculator) {
  // tear stuff down here
}

TEST(Calculator, does_simple_calculations) {
  const char *expr_1[3] = {"1", "+", "0.5"};
  const char *expr_2[3] = {"2", "-", "1"};
  const char *expr_3[3] = {"2", "*", "3"};
  const char *expr_4[3] = {"2", "^", "3"};

  TEST_ASSERT_EQUAL_FLOAT(1.50, calculate(expr_1, 3));
  TEST_ASSERT_EQUAL_FLOAT(1.00, calculate(expr_2, 3));
  TEST_ASSERT_EQUAL_FLOAT(6.00, calculate(expr_3, 3));
  TEST_ASSERT_EQUAL_FLOAT(8.00, calculate(expr_4, 3));
}

TEST(Calculator, does_complex_calculations) {
  const char *expr_1[7] = {"(", "1", "+", "3", ")", "*", "2"};
  const char *expr_2[11] = {"(", "3", "*", "(", "1", "+",
                            "3", ")", ")", "*", "2"};
  const char *expr_3[11] = {"(", "(", "3", "+", "2", ")",
                            "^", "2", ")", "/", "2"};

  TEST_ASSERT_EQUAL_FLOAT(8.00, calculate(expr_1, 7));
  TEST_ASSERT_EQUAL_FLOAT(24.00, calculate(expr_2, 11));
  TEST_ASSERT_EQUAL_FLOAT(12.5, calculate(expr_3, 11));
}

void reset(const char **result) {
  test_num_tokens = 0;
  free(result);
};

TEST(Calculator, split_args_splits_input_simple) {
  char input_1[] = "1 + 3";
  char input_2[] = "1+3";
  char input_3[] = "-1 + 3";
  char input_4[] = "(1 + 3)";
  char input_5[] = "( 1 + 3 )";

  const char *expected_1[3] = {"1", "+", "3"};
  const char *expected_2[3] = {"1", "+", "3"};
  const char *expected_3[3] = {"-1", "+", "3"};
  const char *expected_4[5] = {"(", "1", "+", "3", ")"};
  const char *expected_5[5] = {"(", "1", "+", "3", ")"};

  const char **result_1 = split_args(input_1, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_1, result_1, 3);
  TEST_ASSERT_EQUAL_INT(3, test_num_tokens);
  reset(result_1);

  const char **result_2 = split_args(input_2, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_2, result_2, 3);
  TEST_ASSERT_EQUAL_INT(3, test_num_tokens);
  reset(result_2);

  const char **result_3 = split_args(input_3, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_3, result_3, 3);
  TEST_ASSERT_EQUAL_INT(3, test_num_tokens);
  reset(result_3);

  const char **result_4 = split_args(input_4, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_4, result_4, 5);
  TEST_ASSERT_EQUAL_INT(5, test_num_tokens);
  reset(result_4);

  const char **result_5 = split_args(input_5, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_5, result_5, 5);
  TEST_ASSERT_EQUAL_INT(5, test_num_tokens);
  reset(result_5);
}

// TEST(Calculator, split_ags_splits_input_complex) {
//   char *input_1 = "(1 + 3) * 2";
//   char *input_2 = " ( 1 + 3 ) *2";
//   char *input_3 = "-(1 + 3) * 2";
//   char *input_4 = "- (1 + 3) * 2";
//   char *input_5 = "((1+3) - 2) / 2^2";
//   char *input_6 = "(-(1+3) -2) / 2^-2";
// }