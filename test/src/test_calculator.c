#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"
#include "split_args.h"
#include "unity.h"
#include "unity_fixture.h"

#define length(array) (sizeof(array) / sizeof(*(array)))

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
  const char *expr_5[] = {"-3", "-", "6"};

  TEST_ASSERT_EQUAL_FLOAT(1.50, calculate(expr_1, length(expr_1)));
  TEST_ASSERT_EQUAL_FLOAT(1.00, calculate(expr_2, length(expr_2)));
  TEST_ASSERT_EQUAL_FLOAT(6.00, calculate(expr_3, length(expr_3)));
  TEST_ASSERT_EQUAL_FLOAT(8.00, calculate(expr_4, length(expr_4)));
  TEST_ASSERT_EQUAL_FLOAT(-9.00, calculate(expr_5, length(expr_5)));
}

TEST(Calculator, does_complex_calculations) {
  const char *expr_1[7] = {"(", "1", "+", "3", ")", "*", "2"};
  const char *expr_2[11] = {"(", "3", "*", "(", "1", "+",
                            "3", ")", ")", "*", "2"};
  const char *expr_3[11] = {"(", "(", "3", "+", "2", ")",
                            "^", "2", ")", "/", "2"};
  const char *expr_4[12] = {"-", "(", "(", "3", "+", "2",
                            ")", "^", "2", ")", "/", "2"};

  TEST_ASSERT_EQUAL_FLOAT(8.00, calculate(expr_1, length(expr_1)));
  TEST_ASSERT_EQUAL_FLOAT(24.00, calculate(expr_2, length(expr_2)));
  TEST_ASSERT_EQUAL_FLOAT(12.5, calculate(expr_3, length(expr_3)));
  TEST_ASSERT_EQUAL_FLOAT(-12.5, calculate(expr_4, length(expr_4)));
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
  char input_6[] = "1 - 3";
  char input_7[] = "1.5 - 2.4";
  char input_8[] = "1 + - 3";

  const char *expected_1[3] = {"1", "+", "3"};
  const char *expected_2[3] = {"1", "+", "3"};
  const char *expected_3[3] = {"-1", "+", "3"};
  const char *expected_4[5] = {"(", "1", "+", "3", ")"};
  const char *expected_5[5] = {"(", "1", "+", "3", ")"};
  const char *expected_6[3] = {"1", "-", "3"};
  const char *expected_7[3] = {"1.5", "-", "2.4"};
  const char *expected_8[3] = {"1", "+", "-3"};

  const char **result_1 = split_args(input_1, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_1, result_1, length(expected_1));
  TEST_ASSERT_EQUAL_INT(length(expected_1), test_num_tokens);
  reset(result_1);

  const char **result_2 = split_args(input_2, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_2, result_2, length(expected_2));
  TEST_ASSERT_EQUAL_INT(length(expected_2), test_num_tokens);
  reset(result_2);

  const char **result_3 = split_args(input_3, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_3, result_3, length(expected_3));
  TEST_ASSERT_EQUAL_INT(length(expected_3), test_num_tokens);
  reset(result_3);

  const char **result_4 = split_args(input_4, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_4, result_4, length(expected_4));
  TEST_ASSERT_EQUAL_INT(length(expected_4), test_num_tokens);
  reset(result_4);

  const char **result_5 = split_args(input_5, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_5, result_5, length(expected_5));
  TEST_ASSERT_EQUAL_INT(length(expected_5), test_num_tokens);
  reset(result_5);

  const char **result_6 = split_args(input_6, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_6, result_6, length(expected_6));
  TEST_ASSERT_EQUAL_INT(length(expected_6), test_num_tokens);
  reset(result_6);

  const char **result_7 = split_args(input_7, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_7, result_7, length(expected_7));
  TEST_ASSERT_EQUAL_INT(length(expected_7), test_num_tokens);
  reset(result_7);

  const char **result_8 = split_args(input_8, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_8, result_8, length(expected_8));
  TEST_ASSERT_EQUAL_INT(length(expected_8), test_num_tokens);
  reset(result_8);
}

TEST(Calculator, split_args_splits_input_complex) {
  char input_1[] = "(1 + 3) * 2";
  char input_2[] = " ( 1 + 3 ) *2";
  char input_3[] = "( 1 + 3 ) / 2";
  char input_4[] = "(1 + 3) - 2";
  char input_5[] = "-(1 + 3) * 2";
  char input_6[] = "- (1 + 3) * 2";
  char input_7[] = "((1+3) - 2) / 2^2";
  // char *input_6 = "(-(1+3) -2) / 2^-2";

  const char *expected_1[7] = {"(", "1", "+", "3", ")", "*", "2"};
  const char *expected_2[7] = {"(", "1", "+", "3", ")", "*", "2"};
  const char *expected_3[7] = {"(", "1", "+", "3", ")", "/", "2"};
  const char *expected_4[7] = {"(", "1", "+", "3", ")", "-", "2"};
  const char *expected_5[8] = {"-", "(", "1", "+", "3", ")", "*", "2"};
  const char *expected_6[8] = {"-", "(", "1", "+", "3", ")", "*", "2"};
  const char *expected_7[13] = {"(", "(", "1", "+", "3", ")", "-",
                                "2", ")", "/", "2", "^", "2"};

  const char **result_1 = split_args(input_1, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_1, result_1, length(expected_1));
  TEST_ASSERT_EQUAL_INT(length(expected_1), test_num_tokens);
  reset(result_1);

  const char **result_2 = split_args(input_2, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_2, result_2, length(expected_2));
  TEST_ASSERT_EQUAL_INT(length(expected_2), test_num_tokens);
  reset(result_2);

  const char **result_3 = split_args(input_3, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_3, result_3, length(expected_3));
  TEST_ASSERT_EQUAL_INT(length(expected_3), test_num_tokens);
  reset(result_3);

  const char **result_4 = split_args(input_4, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_4, result_4, length(expected_4));
  TEST_ASSERT_EQUAL_INT(length(expected_4), test_num_tokens);
  reset(result_4);

  const char **result_5 = split_args(input_5, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_5, result_5, length(expected_5));
  TEST_ASSERT_EQUAL_INT(length(expected_5), test_num_tokens);
  reset(result_5);

  const char **result_6 = split_args(input_6, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_6, result_6, length(expected_6));
  TEST_ASSERT_EQUAL_INT(length(expected_6), test_num_tokens);
  reset(result_6);

  const char **result_7 = split_args(input_7, &test_num_tokens);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected_7, result_7, length(expected_7));
  TEST_ASSERT_EQUAL_INT(length(expected_7), test_num_tokens);
  reset(result_7);
}
